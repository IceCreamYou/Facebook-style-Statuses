<?php
// $Id$

/**
 * @file
 *   Handling for cross-posting.
 */

/**
 * Shows either the status owner (if the status was posted to one's own profile)
 * or the status owner and status poster (if the status was posted elsewhere).
 */
class facebook_status_views_handler_field_cross extends views_handler_field {
  function render($values) {
    if ($values->facebook_status_pid && $values->facebook_status_uid) {
      $uid = $values->facebook_status_uid;
      $pid = $values->facebook_status_pid;
    }
    else if ($values->facebook_status_sid) {
      $status = facebook_status_load($values->facebook_status_sid);
      $uid = $status->uid;
      $pid = $status->pid;
    }
    if (isset($uid) && $pid == $uid) {
      return theme('username', user_load(array('uid' => $uid)));
    }
    else {
      $args = array('!poster' => theme('username', user_load(array('uid' => $pid))), '!owner' => theme('username', user_load(array('uid' => $uid))));
      return t('!poster &raquo; !owner', $args);
    }
  }
}