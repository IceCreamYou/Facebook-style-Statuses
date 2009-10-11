<?php
// $Id$

/**
 * @file
 *   Views handler for a "re-post" link.
 */

/**
 * Formats the "re-post" link.
 */
class facebook_status_views_handler_field_repost extends views_handler_field {
  function render($values) {
    $pid = $values->facebook_status_pid;
    if (!$pid) {
      $status = facebook_status_load($values->facebook_status_sid);
      $pid = $status->pid;
    }
    if ((user_access('edit own status') || user_access('edit all statuses')) && $pid != $GLOBALS['user']->uid) {
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $options = array(
        'attributes' => array('class' => 'facebook_status_conversation_link'),
        'query' => array('sid' => $values->facebook_status_sid, 'destination' => $_GET['q'])
      );
      return l(t('Re-post'), 'share-status', $options);
    }
  }
}