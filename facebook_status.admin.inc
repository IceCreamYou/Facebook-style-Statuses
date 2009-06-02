<?php
// $Id$

/**
 * @file
 *   Handles admin pages for the Facebook-style Statuses module.
 */

/**
 * Settings form.
 */
function facebook_status_admin($form_state) {
  $form['facebook_status_concat'] = array(
    '#type' => 'checkbox',
    '#title' => t('Facebook Mode'),
    '#description' => t("Facebook Mode makes this module work like Facebook, where the user's username is appended to the front of the status."),
    '#default_value' => variable_get('facebook_status_concat', 1),
  );
  $form['facebook_status_legacy'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Legacy Mode'),
    '#description' => t('On nodes and/or user profiles, use the status of the author of the node or owner of the profile, respectively, in the status block.'),
    '#default_value' => variable_get('facebook_status_legacy', array('user' => 'user')),
    '#options' => array('node' => t('Nodes'), 'user' => t('User profiles')),
  );
  $form['facebook_status_type'] = array(
    '#type' => 'select',
    '#title' => t('Form type'),
    '#description' => t('Textfields are simpler; textareas are larger and somewhat more confusing for users with JavaScript turned off.'),
    '#default_value' => variable_get('facebook_status_type', 'textfield'),
    '#options' => drupal_map_assoc(array('textfield', 'textarea')),
  );
  $formats = filter_formats();
  $options = array('none' => t('None (HTML escaped)'));
  foreach ($formats as $format) {
    $options[$format->format] = check_plain($format->name);
  }
  $form['facebook_status_filter'] = array(
    '#type' => 'select',
    '#title' => t('Input filter'),
    '#description' => t('This input filter will run on all your statuses, so make sure it is secure.'),
    '#default_value' => variable_get('facebook_status_filter', 1),
    '#options' => $options,
  );
  $form['facebook_status_exclude'] = array(
    '#type' => 'textfield',
    '#title' => t('Exclude users'),
    '#description' => t('Disallow these users from having statuses. Type in usernames separated by commas, following the rules of taxonomy autocomplete fields.'),
    '#default_value' => variable_get('facebook_status_exclude', ''),
    '#maxlength' => 1000,
    '#autocomplete_path' => 'facebook_status/autocomplete',
  );
  $form['facebook_status_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Status update field size'),
    '#description' => t('The width of the status update textfield in the block.'),
    '#default_value' => variable_get('facebook_status_size', 32),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
  );
  $form['facebook_status_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum status length'),
    '#description' => t('Must be a positive integer no greater than 1000.'),
    '#default_value' => variable_get('facebook_status_length', 192),
    '#size' => 3,
    '#maxlength' => 4,
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Validate function for the settings form.
 */
function facebook_status_admin_validate($form, &$form_state) {
  $exclude_string = $form_state['values']['facebook_status_exclude'];
  $exclude_orig = explode(',', $exclude_string);
  $exclude_final = array();
  foreach ($exclude_orig as $excluded) {
    $excluded = trim($excluded);
    $exists = db_result(db_query("SELECT name FROM {users} WHERE name = '%s'", $excluded));
    if ($exists) {
      $exclude_final[] = $excluded;
    }
  }
  $exclude = implode(', ', $exclude_final);
  form_set_value($form['facebook_status_exclude'], $exclude, $form_state);

  $size = $form_state['values']['facebook_status_size'];
  if (!is_numeric($size) || $size < 1 || $size != round($size)) {
    form_set_error('facebook_status_size', t('The size of the status update field must be a positive integer.'));
  }
  $size = $form_state['values']['facebook_status_length'];
  if (!is_numeric($size) || $size < 1 || $size != round($size) || $size > 1000) {
    form_set_error('facebook_status_length', t('The maximum status length must be a positive integer no greater than 1000.'));
  }
}

/**
 * Advanced settings form.
 */
function facebook_status_admin_advanced($form_state) {
  if (module_exists('twitter')) {
    $form['facebook_status_twitter'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow users to post their statuses to Twitter'),
      '#default_value' => variable_get('facebook_status_twitter', 1),
    );
  }
  $form['facebook_status_hide_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide status above textfield'),
    '#default_value' => variable_get('facebook_status_hide_status', 0),
  );
  $form['facebook_status_size_long'] = array(
    '#type' => 'textfield',
    '#title' => t('Long status update field size'),
    '#description' => t('Sometimes, you just need the status update field to be longer than it is in the block. This applies mainly to the "share-status" page.'),
    '#default_value' => variable_get('facebook_status_size_long', 40),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
  );
  $form['facebook_status_flood_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of OpenAPI accesses allowed per IP address per hour'),
    '#description' => t('If you have problems with external sites or applications accessing the open API too often, disable permissions for using it and build RSS feeds in Views instead.'),
    '#default_value' => variable_get('facebook_status_flood_user', 60),
    '#size' => 10,
    '#maxlength' => 10,
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Validate function for the advanced settings form.
 */
function facebook_status_admin_advanced_validate($form, &$form_state) {
  $size = $form_state['values']['facebook_status_size_long'];
  if (!is_numeric($size) || $size < 1 || $size != round($size)) {
    form_set_error('facebook_status_size_long', t('The size of the long status update field must be a positive integer.'));
  }
  $amount = $form_state['values']['facebook_status_flood_user'];
  if (!is_numeric($amount) || $amount < 1 || $amount != round($amount)) {
    form_set_error('facebook_status_flood_user', t('The size of the OpenAPI Access per IP field must be a positive integer.'));
  }
}

/**
 * Autocompletes multiple-username textfields.
 * Some awkwardness exists if a user has quotes or commas in their username.
 * Adapted from taxonomy.module.
 *
 * @param $string
 *   The list of names.
 */
function _facebook_status_user_autocomplete($string = '') {
  $array = drupal_explode_tags($string);
  //The user enters a comma-separated list of names. We only autocomplete the last name.
  $search = trim(array_pop($array));
  $matches = array();
  if ($search != '') {
    $result = db_query_range("SELECT DISTINCT(name) FROM {users}
      WHERE status <> 0 AND uid <> 0 AND LOWER(name) LIKE LOWER('%s%%')
      ORDER BY name ASC", $search, 0, 10);
    $prefix = count($array) ? implode(', ', $array) .', ' : '';
    while ($user = db_fetch_object($result)) {
      $name = $user->name;
      //Commas and quotes in terms are special cases, so encode them.
      //Use strpos() to check if they exist first since str_replace() is costly.
      if (strpos($user->name, ',') !== FALSE || strpos($user->name, '"') !== FALSE) {
        $name = '"'. str_replace('"', '""', $user->name) .'"';
      }
      $matches[$prefix . $name] = check_plain($user->name);
    }
  }
  drupal_json($matches);
}