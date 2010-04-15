<?php
// $Id$

/**
 * @file
 *   Allows sending a status message to every user.
 */

/**
 * Admin form callback.
 */
function facebook_status_announce_admin(&$form_state) {
  $form = array();
  $form['info'] = array(
    '#value' => t('Warning: this can be very slow on sites with lots of users.'),
  );
  $form['from'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender'),
    '#description' => t('The username of the user from whom the messages will be sent.'),
    '#autocomplete_path'  => 'user/autocomplete',
    '#required' => TRUE,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
  );
  $form['send'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );
  return $form;
}

/**
 * Admin form submit callback.
 */
function facebook_status_announce_admin_submit($form, &$form_state) {
  $v = $form_state['values'];
  $from = user_load(array('name' => $v['from']));
  if (!$from->uid) {
    $from = FALSE;
  }

  $count = db_result(db_query("SELECT COUNT(*) FROM {users} WHERE status = 1"));
  $batch = array(
    'operations' => array(
      array('facebook_status_announce_generate_status', array($v['message'], $from, $count)),
    ),
    'finished' => 'facebook_status_announce_batch_finished',
    'title' => t('Sending message to all users'),
    'file' => drupal_get_path('module', 'facebook_status') .'/facebook_status.announce.inc',
  );
  batch_set($batch);
}

/**
 * Sends the status message to users.
 *
 * @param $message
 *   The message that will be sent.
 * @param $from
 *   The $user object of the status poster.
 * @param $count
 *   The number of active users.
 */
function facebook_status_announce_generate_status($message, $from, $count, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
  }
  $uid = db_result(db_query_range("SELECT uid FROM {users} WHERE status = 1", $context['sandbox']['progress'], 1));
  $to = user_load(array('uid' => $uid));
  $options = array(
    'ignore duplicate' => FALSE,
    'ten second override' => FALSE,
    'ignore blank status' => FALSE,
    'alerts' => array(
      'userpoints' => FALSE,
      'hook_facebook_status_save' => TRUE,
      'trigger' => FALSE, //Also calls Activity 2
      'activity1' => FALSE,
      'rules' => TRUE,
      'twitter' => FALSE,
      'appbar' => TRUE,
    ),
  );
  _facebook_status_save_status($to, $from, $message, $options);
  $context['message'] = t('Sending message to %user (@current of @total)',
    array('%user' => $to->name, '@current' => $context['sandbox']['progress'], '@total' => $count));
  $context['sandbox']['progress']++;
  $context['results'][] = check_plain($to->name);
  $context['finished'] = $context['sandbox']['progress'] / $count;
}

/**
 * Batch finished callback.
 */
function facebook_status_announce_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Sent message to @count users: !list',
      array(
        '@count' => count($results),
        '!list' => theme('item_list', $results),
      )
    ));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing %error_operation with arguments: @arguments',
      array(
        '%error_operation' => $error_operation[0],
        '@arguments' => print_r($error_operation[1], TRUE)
      )
    ));
  }
}