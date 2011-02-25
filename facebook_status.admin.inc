<?php

/**
 * @file
 *   Allows users to have a "status."
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
  $form['facebook_status_slide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Slide Effect'),
    '#description' => t('Slides the status update form into a fieldset to reduce the space it takes up.'),
    '#default_value' => variable_get('facebook_status_slide', 1),
  );
  $form['facebook_status_legacy'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Legacy Mode'),
    '#description' => t('On nodes and/or user profiles, use the status of the author of the node or owner of the profile, respectively, in the status block.'),
    '#default_value' => variable_get('facebook_status_legacy', array('user')),
    '#options' => array('node' => t('Nodes'), 'user' => t('User profiles')),
  );
  $form['facebook_status_exclude'] = array(
    '#type' => 'textfield',
    '#title' => t('Exclude users'),
    '#description' => t('Disallow these users from having statuses. Type in usernames separated by commas, following the rules of taxonomy autocomplete fields.'),
    '#default_value' => variable_get('facebook_status_exclude', ''),
    '#maxlength' => 0,
    '#autocomplete_path' => 'facebook_status/autocomplete',
  );
  $form['facebook_status_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Status update field size'),
    '#description' => t('The width of the status update textfield.'),
    '#default_value' => variable_get('facebook_status_size', 32),
    '#size' => 4,
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

/**
 * Not quite sure what I originally intended this to do, but apparently I left off in the middle of it.
  if ($form_state['values']['facebook_status_exclude']) {
    form_set_error('facebook_status_exclude', t('
  }
 */
  $size = $form_state['values']['facebook_status_size'];
  if (!is_numeric($size) || $size < 1 || $size != round($size)) {
    form_set_error('facebook_status_size', t('The size of the status update field must be a positive integer!'));
  }
}