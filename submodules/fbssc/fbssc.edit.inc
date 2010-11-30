<?php
// $Id$

/**
 * @file
 *   Edit and delete forms for the Facebook-style Statuses Comments module.
 */

/**
 * The edit form for status comments.
 *
 * @param $comment
 *   The comment object for the status comment being edited.
 */
function fbssc_edit($form_state, $comment) {
  $form = array();
  $form['status-comment-edit'] = array(
    '#type' => 'textarea',
    '#rows' => 3,
    '#required' => TRUE,
    '#default_value' => $comment->comment,
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  $form['#cid'] = $comment->cid;
  return $form;
}

/**
 * The submit handler for the edit form for status comments.
 */
function fbssc_edit_submit($form, &$form_state) {
  db_query("UPDATE {fbssc} SET comment = '%s' WHERE cid = %d", $form_state['values']['status-comment-edit'], $form['#cid']);
  $c = fbssc_load($form['#cid']);
  module_invoke_all('fbss_after_save', $c, TRUE);
  if ($_GET['destination'] && $_GET['destinaton'] != 'fbssc/js') {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = '<front>';
  }
  drupal_set_message(t('Status comment has been successfully edited.'));
}

/**
 * The delete form for status comments.
 *
 * @param $comment
 *   The comment object for the status comment being deleted.
 */
function fbssc_delete($form_state, $comment) {
  $form = array();
  $form['infotext'] = array(
    '#value' => '<p>'. t('Are you sure you want to permanently delete the status comment %comment?',
      array('%comment' => $comment->comment)) .'</p>'
  );
  $form['confirm'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm'),
    '#submit' => array('fbssc_delete_confirm'),
  );
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('fbssc_delete_cancel'),
  );
  $form['#cid'] = $comment->cid;
  return $form;
}

/**
 * The confirmation submit handler for the delete form for status comments.
 */
function fbssc_delete_confirm($form, &$form_state) {
  fbssc_delete_comment($form['#cid']);
  drupal_set_message(t('Status comment deleted.'));
  if ($_GET['destination'] && $_GET['destinaton'] != 'fbssc/js') {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = '<front>';
  }
}

/**
 * The cancellation submit handler for the delete form for status comments.
 */
function fbssc_delete_cancel($form, &$form_state) {
  drupal_set_message(t('Status comment was not deleted.'));
  if ($_GET['destination'] && $_GET['destinaton'] != 'fbssc/js') {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = '<front>';
  }
}