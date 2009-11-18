<?php
// $Id$

/**
 * @file
 *   Handling for the poster's name.
 */

/**
 * Allows linking to the poster of the status.
 */
class facebook_status_views_handler_field_poster extends views_handler_field_user {
  function render($values) {
    if ($values->facebook_status_pid) {
      $account = user_load(array('uid' => $values->facebook_status_pid));
      if (!empty($this->options['link_to_user'])) {
        return theme('username', $account);
      }
      return check_plain($account->name);
    }
    elseif ($values->facebook_status_sid) {
      $status = facebook_status_load($values->facebook_status_sid);
      $account = user_load(array('uid' => $status->pid));
      if (!empty($this->options['link_to_user'])) {
        return theme('username', $account);
      }
      return check_plain($account->name);
    }
  }
}