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
    '#weight' => -45,
  );
  $form['facebook_status_legacy'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Legacy Mode'),
    '#description' => t('On nodes and/or user profiles, use the status of the author of the node or owner of the profile, respectively, in the status block.'),
    '#default_value' => variable_get('facebook_status_legacy', array('user' => 'user')),
    '#options' => array('node' => t('Nodes'), 'user' => t('User profiles')),
    '#weight' => -40,
  );
  if (module_exists('twitter')) {
    $form['facebook_status_twitter_default'] = array(
      '#type' => 'radios',
      '#title' => t('Default Twitter option'),
      '#default_value' => variable_get('facebook_status_twitter_default', 'off'),
      '#required' => TRUE,
      '#options' => array(
        'on' => t('Always enabled by default'),
        'off' => t('Always disabled by default'),
        'on-user' => t('Let the user choose (enabled is default)'),
        'off-user' => t('Let the user choose (disabled is default)'),
        'disallow' => t('Do not allow posting to Twitter at all'),
      ),
      '#weight' => -30,
    );
  }
  $form['facebook_status_type'] = array(
    '#type' => 'select',
    '#title' => t('Form type'),
    '#description' => t('Textfields are simpler; textareas are larger and somewhat more confusing for users with JavaScript turned off.'),
    '#default_value' => variable_get('facebook_status_type', 'textarea'),
    '#options' => drupal_map_assoc(array('textarea', 'textfield')),
    '#weight' => -20,
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
    '#default_value' => variable_get('facebook_status_filter', 'none'),
    '#options' => $options,
    '#weight' => -20,
  );
  $form['facebook_status_exclude'] = array(
    '#type' => 'textfield',
    '#title' => t('Exclude users'),
    '#description' => t('Disallow these users from having statuses. Type in usernames separated by commas, following the rules of taxonomy autocomplete fields.'),
    '#default_value' => variable_get('facebook_status_exclude', ''),
    '#maxlength' => 1000,
    '#autocomplete_path' => 'facebook_status/autocomplete',
    '#weight' => -10,
  );
  $form['facebook_status_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Status update field size'),
    '#description' => t('The width of the status update textfield in the block.'),
    '#default_value' => variable_get('facebook_status_size', 32),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#weight' => -10,
  );
  $form['facebook_status_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum status length'),
    '#description' => t('Must be a positive integer no greater than 21844.'),
    '#default_value' => variable_get('facebook_status_length', 140),
    '#size' => 3,
    '#maxlength' => 5,
    '#required' => TRUE,
    '#weight' => -10,
  );
  $form['facebook_status_repost'] = array(
    '#type' => 'textfield',
    '#title' => t('Re-post format'),
    '#description' => t("The format of the default message when users click a link to re-post a status. @name will be replaced with the poster's name and @status will be replaced with the status text."),
    '#default_value' => variable_get('facebook_status_repost', 'Re: @name @status '),
    '#weight' => -10,
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
  //21844 is 65535 / 3 - 1. In MySQL, 65535 is the maximum number of bytes a
  //text column can hold, and in UTF8 each character takes 3 bytes of storage.
  $size = $form_state['values']['facebook_status_length'];
  if (!is_numeric($size) || $size < 1 || $size != round($size) || $size > 21844) {
    form_set_error('facebook_status_length', t('The maximum status length must be a positive integer no greater than 21844.'));
  }
  if ($size > 140 && module_exists('twitter') && variable_get('facebook_status_twitter_default', 'off') != 'disallow') {
    drupal_set_message(t('The maximum number of characters allowed in a status is set to a number above 140, and users can post status updates to Twitter. These settings could allow users to post messages to Twitter which are too long for Twitter to handle, in which case Twitter will cut short those messages.'), 'warning');
  }
}

/**
 * Advanced settings form.
 */
function facebook_status_admin_advanced($form_state) {
  $form['facebook_status_refresh'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show AJAX "Refresh" link after status update views'),
    '#description' => t('Display a "Refresh" link under content that will be automatically refreshed when the status update form is submitted.') .
      t('Clicking the link will similarly update the related content via JavaScript, without refreshing the page.') .
      t('Obviously, the "Refresh" link will only appear when there is something that can be refreshed.') .
      t('If you disable AHAH refreshing below or if you have no views attached to your status update forms, this setting is useless.'),
    '#default_value' => variable_get('facebook_status_refresh', 0),
    '#weight' => -34,
  );
  $form['facebook_status_hide_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide status above textfield'),
    '#default_value' => variable_get('facebook_status_hide_status', 0),
    '#weight' => -33,
  );
  $form['facebook_status_hide_blank'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide blank and empty statuses above textfield'),
    '#default_value' => variable_get('facebook_status_hide_blank', 0),
    '#weight' => -32,
  );
  $form['facebook_status_nl2br'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert line breaks'),
    '#description' => t('By default, line breaks in the status update form are ignored. If you use an input filter to fix that, the status text will appear on a different line than the username and other information. Enabling this setting allows line breaks to appear without the side-effect of the input filter.'),
    '#default_value' => variable_get('facebook_status_nl2br', 0),
    '#weight' => -31,
  );
  $form['facebook_status_ahah'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use AHAH to refresh the status update form without refreshing the page'),
    '#description' => t("You should leave this checked unless you know what you're doing."),
    '#default_value' => variable_get('facebook_status_ahah', 1),
    '#weight' => -30,
  );
  if (module_exists('views')) {
    $views = views_get_all_views();
    $list = array('' => t('None'));
    foreach ($views as $name => $view) {
      if ($view->disabled == 0) {
        $list[$name] = $name;
      }
    }
    $form['facebook_status_profile_view'] = array(
      '#type' => 'select',
      '#title' => t('Show a view on the profile'),
      '#description' => t('This is only relevant for the core profile, meaning it will not work if you override the default profile. <strong>The default facebook_status view is recommended. Other views may not work correctly.</strong>'),
      '#default_value' => variable_get('facebook_status_profile_view', $list['facebook_status']),
      '#options' => $list,
      '#weight' => -22,
    );
    $form['facebook_status_share_view'] = array(
      '#type' => 'select',
      '#title' => t('Show a view on the share-status page'),
      '#description' => t('The default facebook_status view is recommended.'),
      '#default_value' => variable_get('facebook_status_share_view', $list['facebook_status']),
      '#options' => $list,
      '#weight' => -21,
    );
    $form['facebook_status_reply_type'] = array(
      '#type' => 'select',
      '#title' => t('Reply method'),
      '#default_value' => variable_get('facebook_status_reply_type', 'at'),
      '#options' => array(
        'at' => t('Reply by @username reference'),
        'convo' => t('Reply in conversation view'),
      ),
      '#weight' => -20,
    );
  }
  $form['facebook_status_size_long'] = array(
    '#type' => 'textfield',
    '#title' => t('Long status update field size'),
    '#description' => t('Sometimes, you just need the status update field to be longer than it is in the block. This applies mainly to the "share-status" page.'),
    '#default_value' => variable_get('facebook_status_size_long', 40),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#weight' => -14,
  );
  $form['facebook_status_box_rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of rows of the status update box'),
    '#description' => t('This only applies if the status update box type is set to "textarea" (not "textfield").'),
    '#default_value' => variable_get('facebook_status_box_rows', 2),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#weight' => -13,
  );
  $form['facebook_status_flood_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of OpenAPI accesses allowed per IP address per hour'),
    '#description' => t('If you have problems with external sites or applications accessing the open API too often, disable permissions for using it and build RSS feeds in Views instead.'),
    '#default_value' => variable_get('facebook_status_flood_user', 60),
    '#size' => 10,
    '#maxlength' => 10,
    '#required' => TRUE,
    '#weight' => -12,
  );
  $form['facebook_status_default_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Default text'),
    '#description' => t('If you leave this as @laststatus, the default text in the status update form will be the last status, if it exists; '.
      'if no statuses have been posted or the last status was blank, you can translate the default text '.
      '(blank by default, identified by "@fbssdefault" in the translation interface). Otherwise, the text you input here '.
      'will appear in the status update form and will not be translatable. In both cases, the default text will be '.
      'automatically cleared when a user clicks in the status update box.'),
    '#default_value' => variable_get('facebook_status_default_text', '@laststatus'),
    '#weight' => -10,
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
  $size = $form_state['values']['facebook_status_box_rows'];
  if (!is_numeric($size) || $size < 1 || $size != round($size)) {
    form_set_error('facebook_status_box_rows', t('The number of rows of the status update box must be a positive integer.'));
  }
  $amount = $form_state['values']['facebook_status_flood_user'];
  if (!is_numeric($amount) || $amount < 1 || $amount != round($amount)) {
    form_set_error('facebook_status_flood_user', t('The number of OpenAPI Accesses per IP must be a positive integer.'));
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