<?php
// $Id$

/**
 * @file
 *   Provides edit/delete status forms.
 */

/**
 * The edit status form.
 */
function _facebook_status_edit(&$form_state, $status) {
  $size = variable_get('facebook_status_size_long', 40);
  $maxlength = variable_get('facebook_status_length', 192);
  $account = user_load(array('uid' => $status->uid));
  //Because this text will appear exactly as-is in the textfield, we can't use a full check_plain() or filter_xss().
  $default = str_replace('"', '', $status->status);

  if (variable_get('facebook_status_concat', 1)) {
    $prefix = '<span class="facebook_status_prefix">'. t('!fbss_prefix_name ', array('!fbss_prefix_name' => theme('username', $account))) .'&nbsp;</span>';
  }
  else {
    $prefix = '';
  }

  $path = drupal_get_path('module', 'facebook_status');
  drupal_add_js($path .'/facebook_status.js');
  drupal_add_css($path .'/facebook_status.css');
  drupal_add_js(array('facebook_status' => array(
    'maxlength' => $maxlength,
    'ttype' => variable_get('facebook_status_type', 'textfield'))
  ), 'setting');
  //Don't show the slider; we'd have to do a custom version of theme('facebook_status_item').
  $slider = '';
  $form = array('#cache' => TRUE);
  $form['slider'] = array(
    '#prefix' => '<span id="facebook_status_replace">',
    '#value' => '<span id="facebook_status_slider">'. $slider .'</span>',
  );
  $form['status'] = array(
    '#type' => variable_get('facebook_status_type', 'textfield'),
    '#field_prefix' => $prefix,
    '#size' => $size,
    '#cols' => $size,
    '#rows' => 2,
    '#maxlength' => $maxlength,
    '#default_value' => $default,
    '#attributes' => array('class' => 'facebook_status_text'),
    '#suffix' => '</span>',
    '#resizable' => FALSE,
  );
  $form['sid'] = array(
    '#type' => 'value',
    '#value' => $status->sid,
  );
  $form['fbss-submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => 'facebook_status_submit'),
  );
  $form['chars'] = array(
    '#value' => '<span id="facebook_status_chars">'. t('%chars characters allowed', array('%chars' => $maxlength)) .'</span>',
  );
  //@todo: This is bad. It should be in the CSS but that doesn't seem to be working.
  $form['#attributes'] = array('style' => 'margin-bottom: 0;');
  return $form;
}

/**
 * Validate function for the status update form.
 */
function _facebook_status_edit_validate($form, &$form_state) {
  $maxlen = variable_get('facebook_status_length', 192);
  if (drupal_strlen($form_state['values']['status']) > $maxlen) {
    form_set_error('status', t('The status must be no longer than %chars characters.', array('%chars' => $maxlen)));
  }
}

/**
 * Submit function for the status update form.
 */
function _facebook_status_edit_submit($form, &$form_state) {
  $status_old = facebook_status_load($form_state['values']['sid']);
  $account = user_load(array('uid' => $status_old->uid));
  $new_status = trim($form_state['values']['status']);

  global $user;
  //If the user clears the status, set the time to zero so the new, blank status will not show up as new in lists.
  $time = time();
  if ($new_status === '') {
    $time = 0;
  }
  //Pretend to have set a new status if the submitted status is exactly the same as the old one.
  if ($new_status != $status_old->status && $account->uid) {
    $sql = "UPDATE {facebook_status} SET status = '%s', status_time = %d WHERE sid = %d ORDER BY sid DESC";
    db_query($sql, $new_status, $time, $status_old->sid);
    //Invokes hook_facebook_status_save($status_owner_object, &$status, $sid).
    module_invoke_all('facebook_status_save', $account, $new_status, $status_old->sid);
  }

  if ($_GET['destination']) {
    $form_state['redirect'] = array($_GET['destination']);
  }
  else {
    $form_state['redirect'] = array('share-status');
  }
  drupal_set_message(t('Status has been successfully edited.'));
}

/**
 * The delete status confirmation form.
 */
function _facebook_status_delete(&$form_state, $status) {
  $form['infotext'] = array('#value' => t('Are you sure you want to permanently delete the status %status?', array('%status' => $status->status)));
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
  $form['status'] = array(
    '#type' => 'value',
    '#value' => $status->sid,
  );
  return $form;
}

/**
 * Deletes a status.
 */
function _facebook_status_delete_confirm($form, &$form_state) {
  facebook_status_delete_status($form_state['values']['status']);
  drupal_set_message(t('Status deleted.'));
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