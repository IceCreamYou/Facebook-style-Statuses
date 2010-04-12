<?php
// $Id$

/**
 * @file
 *   Provides Devel Generate integration.
 */

/**
 * The Generate statuses form.
 */
function facebook_status_generate_form($form_state) {
  $form['killswitch'] = array(
    '#type' => 'checkbox',
    '#title' => t('<strong>Delete all statuses</strong> before generating new content'),
    '#default_value' => FALSE,
  );
  if (module_exists('facebook_status_tags')) {
    $form['tags'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include #hashtags and @userreferences in the statuses'),
      '#default_value' => FALSE,
    );
  }
  $form['respond'] = array(
    '#type' => 'checkbox',
    '#title' => t("Make some generated statuses be posted to other users' streams"),
    '#default_value' => FALSE,
  );
  $options = array(1 => t('Now'));
  foreach (array(3600, 86400, 604800, 2592000, 31536000) as $interval) {
    $options[$interval] = t('!time ago', array('!time' => format_interval($interval, 1)));
  }
  $form['time'] = array(
    '#type' => 'select',
    '#title' => t('How far back in time should the statuses be dated?'),
    '#description' => t('Status creation dates will be distributed randomly from the current time back to the selected time.'),
    '#options' => $options,
    '#default_value' => 604800,
    '#required' => TRUE,
  );
  $form['num'] = array(
    '#type' => 'textfield',
    '#title' => t('How many statuses would you like to generate?'),
    '#default_value' => 50,
    '#size' => 10,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Do it!'),
  );
  return $form;
}

/**
 * The validation handler for the Generate statuses form.
 */
function facebook_status_generate_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['num']) || $form_state['values']['num'] < 0) {
    form_set_error('num', t('You must generate at least 0 statuses.'));
  }
}

/**
 * The submit handler for the Generate statuses form.
 */
function facebook_status_generate_form_submit($form, &$form_state) {
  $v = $form_state['values'];
  $operations = array();
  if ($v['killswitch']) {
    $operations[] = array('facebook_status_generate_killswitch', array());
  }
  if ($v['num'] > 50 || $v['killswitch']) {
    for ($i = 0; $i < $v['num']; $i++) {
      $operations[] = array('facebook_status_generate_status', array($v['time'], $v['respond'], $v['tags']));
    }
    batch_set(array(
      'title' => t('Generating statuses'),
      'operations' => $operations,
      'finished' => 'facebook_status_generate_finished',
      'file' => drupal_get_path('module', 'facebook_status') .'/facebook_status.generate.inc',
    ));
  }
  else {
    $context = array('results' => array('num' => 0));
    for ($i = 0; $i < $v['num']; $i++) {
      facebook_status_generate_status($v['time'], $v['respond'], $v['tags'], $context);
    }
    facebook_status_generate_finished(TRUE, $context, array());
  }
}

/**
 * Generates a status.
 *
 * @param $time
 *   The number of seconds ago that corresponds to the created time of the
 *   oldest status we could create.
 * @param $respond
 *   TRUE to make some statuses be posts to other users' streams.
 * @param $tags
 *   TRUE to make some statuses include #hashtags and @userreferences.
 */
function facebook_status_generate_status($time, $respond, $tags, &$context) {
  module_load_include('inc', 'devel', 'devel_generate');
  $stime = time() - mt_rand(0, $time);
  $uids = devel_get_users();
  $uid = 0;
  while ($uid == 0) {
    $uid = $uids[array_rand($uids)];
  }
  $pid = $uid;
  if ($respond && mt_rand(0, 1)) {
    $pid = $uids[array_rand($uids)];
    while ($pid == 0) {
      $pid = $uids[array_rand($uids)];
    }
  }
  $text = '';
  //User references.
  if (module_exists('facebook_status_tags') && $tags && $uid == $pid && mt_rand(0, 1)) {
    $rid = 0;
    while ($rid == 0 || $rid == $uid) {
      $rid = $uids[array_rand($uids)];
    }
    $person = user_load(array('uid' => $rid));
    $text .= '@'. $person->name .' ';
    if (preg_match('/.+\b.+/', $person->name)) {
      $text .= '[@'. $person->name .'] ';
    }
  }
  $mtext = devel_create_greeking(mt_rand(2, variable_get('facebook_status_length', 140) / 7));
  $text .= drupal_substr($mtext, 0, variable_get('facebook_status_length', 140) - drupal_strlen($text));
  //Hashtags.
  if (module_exists('facebook_status_tags') && $tags && variable_get('facebook_status_tags_vid', -1) != -1 && mt_rand(0, 2) > 0) {
    $word = devel_generate_word(mt_rand(3, 7));
    if (drupal_strlen($text . $word) + 2 <= variable_get('facebook_status_length', 140)) {
      $text .= ' #'. $word;
    }
    $word = devel_generate_word(mt_rand(3, 5));
    $word2 = devel_generate_word(mt_rand(3, 5));
    if (drupal_strlen($text . $word . $word2) + 5 <= variable_get('facebook_status_length', 140)) {
      $text .= ' [#'. $word .' '. $word2 .']';
    }
  }
  $status = (object) array('status' => $text, 'status_time' => $stime, 'uid' => $uid, 'pid' => $pid);
  drupal_write_record('facebook_status', $status);
  $account = user_load(array('uid' => $uid));
  $status->owner = $account;
  module_invoke_all('facebook_status_save', $status, FALSE);
  $context['results']['num']++;
}

/**
 * Deletes all statuses.
 */
function facebook_status_generate_killswitch(&$context) {
  $result = db_query("SELECT sid FROM {facebook_status}");
  $i = 0;
  while ($status = db_fetch_object($result)) {
    facebook_status_delete_status($status->sid);
    $i++;
  }
  drupal_set_message(format_plural($i, 'Deleted one status', 'Deleted @count statuses'));
}

/**
 * Alerts user that the batch processing is complete.
 */
function facebook_status_generate_finished($success, $results, $operations) {
  $message = t('Finished creating statuses with an error.');
  if ($success && $results['num']) {
    $message = t('Finished creating @num statuses sucessfully.', array('@num' => $results['num']));
  }
  elseif ($success) {
    $message = t('Finished processing 0 statuses.');
  }
  drupal_set_message($message);
}