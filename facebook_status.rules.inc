<?php
// $Id$

/**
 * @file
 *   Rules integration.
 */

/**
 * Implementation of hook_rules_event_info().
 */
function facebook_status_rules_event_info() {
  return array(
    'facebook_status_delete' => array(
      'label' => t('User deletes a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status.')),
      ),
    ),
    'facebook_status_edit' => array(
      'label' => t('User edits a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status.')),
      ),
    ),
    'facebook_status_update' => array(
      'label' => t('User adds or updates a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'owner' => array('type' => 'user', 'label' => t('The user to whose profile the status was posted.')),
        'poster' => array('type' => 'user', 'label' => t('The user who posted the status.')),
        'status' => array('type' => 'facebook_status', 'label' => t('The status object.')),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_condition_info().
 */
function facebook_status_rules_condition_info() {
  return array(
    'facebook_status_is_self' => array(
      'label' => t('Status was posted to own profile'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'facebook_status_can_post' => array(
      'label' => t('User has permission to send a status-message'),
      'arguments' => array(
        'owner' => array('type' => 'user', 'label' => t('Owner')),
        'poster' => array('type' => 'user', 'label' => t('Poster')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'facebook_status_rules_condition_can_edit' => array(
      'label' => t('User has permission to edit a status'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'facebook_status_rules_condition_can_delete' => array(
      'label' => t('User has permission to delete a status'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
  );
}

/**
 * Checks if the status was posted to the user's own profile.
 */
function facebook_status_is_self($status) {
  return $status->uid == $status->pid;
}

/**
 * Checks if the current user can edit the status.
 */
function facebook_status_rules_condition_can_edit($status) {
  _facebook_status_can_edit($status);
}

/**
 * Checks if the current user can delete the status.
 */
function facebook_status_rules_condition_can_delete($status) {
  _facebook_status_can_edit($status, TRUE);
}

/**
 * Implementation of hook_rules_action_info().
 */
function facebook_status_rules_action_info() {
  return array(
    'facebook_status_load_action' => array(
      'label' => t('Load a status'),
      'new variables' => array(
        'status_loaded' => array('type' => 'facebook_status', 'label' => t('Loaded status')),
      ),
      'help' => t('Enter the Status ID of a status to load.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sid'),
    ),
    'facebook_status_edit_action' => array(
      'label' => t('Edit a status'),
      'help' => t('Enter the Status ID of the status to edit and the text you wish to replace the status.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sid', 'status'),
    ),
    'facebook_status_delete_action' => array(
      'label' => t('Delete a status'),
      'help' => t('Enter the Status ID of the status to delete.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sid'),
    ),
    'facebook_status_add_action' => array(
      'label' => t('Add a status'),
      'help' => t('Enter the status text and the User ID or Username of the user to whose profile the status will be posted.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('poster', 'uid', 'name', 'status'),
    ),
  );
}

/**
 * Builds the form for loading a status.
 */
function facebook_status_load_action_form($settings, &$form) {
  $settings += array('sid' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
}

/**
 * Loads a status.
 */
function facebook_status_load_action($settings) {
  return array('status_loaded' => facebook_status_load($settings['sid']));
}

/**
 * Builds the form for editing a status.
 */
function facebook_status_edit_action_form($settings, &$form) {
  $settings += array('sid' => '', 'status' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
  $form['settings']['status'] = array(
    '#type' => 'textarea',
    '#title' => t('Status'),
    '#default_value' => $settings['status'],
    '#rows' => 3,
  );
}

/**
 * Edits a status.
 */
function facebook_status_edit_action($settings) {
  $status_old = facebook_status_load($settings['sid']);
  $account = user_load(array('uid' => $status_old->uid));
  $new_status = trim($settings['status']);
  global $user;
  //If the user clears the status, set the time to zero so the new, blank status will not show up as new in lists.
  $time = $status_old->status_time;
  if ($new_status === '') {
    $time = 0;
  }
  //Don't set a new status if the submitted status is exactly the same as the old one.
  if ($new_status != $status_old->status && $account->uid) {
    $sql = "UPDATE {facebook_status} SET status = '%s', status_time = %d WHERE sid = %d ORDER BY sid DESC";
    db_query($sql, $new_status, $time, $status_old->sid);
    //Invokes hook_facebook_status_save($status_owner_object, &$status, $sid).
    module_invoke_all('facebook_status_save', $account, $new_status, $status_old->sid);
  }
  //Trigger integration.
  if (module_exists('trigger')) {
    module_invoke_all('facebook_status', 'fbss_edited', $status_old->sid);
  }
  //Rules integration.
  if (module_exists('rules')) {
    rules_invoke_event('facebook_status_edit', $status_old->sid);
  }
}

/**
 * Builds the form for deleting a status.
 */
function facebook_status_delete_action_form($settings, &$form) {
  $settings += array('sid' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
}

/**
 * Deletes a status.
 */
function facebook_status_delete_action($settings) {
  facebook_status_delete_status($settings['sid']);
}

/**
 * Builds the form for adding a status.
 */
function facebook_status_add_action_form($settings, &$form) {
  $settings += array('poster' => '', 'uid' => '', 'name' => '', 'status' => '');
  $form['settings']['poster'] = array(
    '#type' => 'textfield',
    '#title' => t('Poster username'),
    '#autocomplete_path' => 'user/autocomplete',
    '#description' => t('If you leave this blank, the current user will be assumed.'),
    '#default_value' => $settings['poster'],
  );
  $form['settings']['uid'] = array(
    '#type' => 'textfield',
    '#title' => t('Owner user ID'),
    '#default_value' => $settings['uid'],
  );
  $form['settings']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Owner username'),
    '#default_value' => $settings['name'],
  );
  $form['settings']['status'] = array(
    '#type' => 'textarea',
    '#title' => t('Status'),
    '#default_value' => $settings['status'],
    '#rows' => 3,
  );
}

/**
 * Validates the form for adding a status.
 */
function facebook_status_add_action_validate($form, $form_state) {
  if (!$form_state['values']['settings']['uid'] && !$form_state['values']['settings']['name']) {
    form_set_error('settings][uid', t('You must enter either a User ID or Username (or both).'));
  }
}

/**
 * Adds a status.
 */
function facebook_status_add_action($settings) {
  $status = $settings['status'];
  $from = user_load(array('name' => $settings['poster']));
  if (!$from->uid) {
    $from = FALSE;
  }
  if ($settings['uid'] && $settings['name']) {
    $to = user_load(array('uid' => $settings['uid'], 'name' => $settings['name']));
  }
  elseif ($settings['uid']) {
    $to = user_load(array('uid' => $settings['uid']));
  }
  elseif ($settings['name']) {
    $to = user_load(array('name' => $settings['name']));
  }
  else {
    $to = FALSE;
  }
  _facebook_status_save_status($to, $from, $status);
}

/**
 * Implementation of hook_rules_data_type_info().
 */
function facebook_status_rules_data_type_info() {
  return array(
    'facebook_status' => array(
      'label' => t('Facebook-style Status'),
      'class' => 'rules_data_type_facebook_status',
      'savable' => TRUE,
      'identifiable' => TRUE,
      'use_input_form' => FALSE,
      'module' => 'Facebook-style Statuses',
    ),
  );
}

/**
 * Defines the rules node data type.
 */
class rules_data_type_facebook_status extends rules_data_type {
  function save() {
    $status = &$this->get();
    _facebook_status_save_status(user_load(array('uid' => $status->uid)), user_load(array('uid' => $status->pid)), $status->status);
    return TRUE;
  }
  function load($sid) {
    return facebook_status_load($sid);
  }
  function get_identifier() {
    $status = &$this->get();
    return $status->sid;
  }
}