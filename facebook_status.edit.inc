<?php
// $Id$

/**
 * @file
 *   Provides edit/delete status forms.
 */

/**
 * The edit status form.
 */
function facebook_status_edit(&$form_state, $status) {
  $size = variable_get('facebook_status_size_long', 40);
  $maxlength = variable_get('facebook_status_length', 140);
  $account = user_load(array('uid' => $status->uid));
  $default = $status->status;

  if (variable_get('facebook_status_concat', 1)) {
    $prefix = '<span class="facebook_status_prefix">'. t('!fbss_prefix_name', array('!fbss_prefix_name' => theme('username', $account))) .'&nbsp;&nbsp;</span>';
  }
  else {
    $prefix = '';
  }

  $path = drupal_get_path('module', 'facebook_status');
  drupal_add_js($path .'/facebook_status.js');
  drupal_add_css($path .'/facebook_status.css');
  global $user;
  $orig = nl2br(check_plain($status->status));
  if ($user->uid == $status->pid && $status->pid == $status->uid) {
    $slider = '<strong>'. t('Original status: !status', array('!status' => $orig)) .' </strong>';
  }
  elseif ($user->uid != $status->pid && $status->pid == $status->uid) {
    $args = array('!user' => theme('username', user_load(array('uid' => $status->pid))), '!status' => $orig);
    $slider = '<strong>'. t('Original status by !user: !status', $args) .' </strong>';
  }
  elseif ($status->pid != $status->uid) {
    $owner = $poster = t('you');
    if ($user->uid != $status->uid) {
      $owner = theme('username', user_load(array('uid' => $status->uid)));
    }
    if ($user->uid != $status->pid) {
      $poster = theme('username', user_load(array('uid' => $status->pid)));
    }
    $args = array('!poster' => $poster, '!owner' => $owner, '!status' => $orig);
    $slider = '<strong>'. t('Original message from !poster to !owner: !status', $args) .' </strong>';
  }
  $form = array('#cache' => TRUE);
  $form['slider'] = array(
    '#value' => '<div class="facebook_status_update clear-block"><span class="facebook_status_slider">'. $slider .'</span>',
    '#weight' => -45,
  );
  $form['fbss-status'] = array(
    '#type' => variable_get('facebook_status_type', 'textarea'),
    '#field_prefix' => $prefix,
    '#size' => $size,
    '#cols' => $size,
    '#rows' => variable_get('facebook_status_box_rows', 2),
    '#maxlength' => $maxlength,
    '#default_value' => $default,
    '#attributes' => array('class' => 'facebook_status_text'),
    '#resizable' => FALSE,
    '#weight' => -40,
  );
  $form['chars'] = array(
    '#value' => '<span id="facebook_status_chars">'. t('%chars characters allowed', array('%chars' => $maxlength)) .'</span>',
    '#weight' => -38,
  );
  $form['sid'] = array(
    '#type' => 'value',
    '#value' => $status->sid,
    '#weight' => -35,
  );
  $form['fbss-submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => 'facebook_status_submit'),
    '#suffix' => '</div>',
    '#weight' => -25,
  );
  //@todo: This is bad. It should be in the CSS but that doesn't seem to be working.
  $form['#attributes'] = array('style' => 'margin-bottom: 0;');
  return $form;
}

/**
 * Validate function for the status update form.
 */
function facebook_status_edit_validate($form, &$form_state) {
  $maxlen = variable_get('facebook_status_length', 192);
  if (drupal_strlen($form_state['values']['fbss-status']) > $maxlen) {
    form_set_error('status', t('The status must be no longer than %chars characters.', array('%chars' => $maxlen)));
  }
}

/**
 * Submit function for the status update form.
 */
function facebook_status_edit_submit($form, &$form_state) {
  $status_old = facebook_status_load($form_state['values']['sid']);
  $account = user_load(array('uid' => $status_old->uid));
  $new_status = trim($form_state['values']['fbss-status']);

  global $user;
  //If the user clears the status, set the time to zero so the new, blank status will not show up as new in lists.
  $time = $status_old->status_time;
  if ($new_status === '') {
    $time = 0;
  }
  //Pretend to have set a new status if the submitted status is exactly the same as the old one.
  if ($new_status != $status_old->status && $account->uid) {
    $sql = "UPDATE {facebook_status} SET status = '%s', status_time = %d WHERE sid = %d ORDER BY sid DESC";
    db_query($sql, $new_status, $time, $status_old->sid);
    //Invokes hook_facebook_status_save($status, $edit).
    $status_old->status = $new_status;
    $status_old->status_time = $time;
    $status_old->owner = $account;
    module_invoke_all('facebook_status_save', $status_old, TRUE);
  }

  if ($_GET['destination']) {
    $form_state['redirect'] = array($_GET['destination']);
  }
  else {
    $form_state['redirect'] = array('share-status');
  }
  drupal_set_message(t('Status has been successfully edited.'));
  //Trigger integration.
  if (module_exists('trigger')) {
    module_invoke_all('facebook_status', 'fbss_edited', $status_old->sid);
  }
  //Rules integration.
  if (module_exists('rules')) {
    $status_old->status = $new_status;
    $status_old->status_time = $time;
    rules_invoke_event('facebook_status_edit', $status_old);
  }
  //Pathauto integration.
  if (module_exists('pathauto')) {
    $op = 'update';
    module_load_include('inc', 'pathauto');
    $placeholders = pathauto_get_placeholders('facebook_status', $status_old);
    $src = 'statuses/'. $status_old->sid;
    $type = ($status_old->uid == $status_old->pid) ? 'self' : 'other';
    pathauto_create_alias('facebook_status', $op, $placeholders, $src, $type);
  }
}

/**
 * The delete status confirmation form.
 */
function _facebook_status_delete(&$form_state, $status) {
  $form['infotext'] = array('#value' => '<p>'. t('Are you sure you want to permanently delete the status %status?', array('%status' => $status->status)) .'</p>');
  $form['confirm'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm'),
    '#submit' => array('_facebook_status_delete_confirm'),
  );
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('_facebook_status_delete_cancel'),
  );
  $form['status-sid'] = array(
    '#type' => 'value',
    '#value' => $status->sid,
  );
  return $form;
}

/**
 * Deletes a status.
 */
function _facebook_status_delete_confirm($form, &$form_state) {
  facebook_status_delete_status($form_state['values']['status-sid']);
  drupal_set_message(t('Status deleted.'));
  if ($_GET['destination']) {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = 'user';
  }
}

/**
 * Cancels status deletion.
 */
function _facebook_status_delete_cancel($form, &$form_state) {
  if ($_GET['destination']) {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = 'user';
  }
}