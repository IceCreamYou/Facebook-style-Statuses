<?php
// $Id$

/**
 * @file
 *   Handling for the poster's picture in Views.
 */

/**
 * Shows the profile picture for the user who posted the status.
 */
class facebook_status_views_handler_field_poster_pic extends views_handler_field {
  function render($values) {
    if ($values->facebook_status_pid) {
      $pid = $values->facebook_status_pid;
    }
    elseif ($values->facebook_status_sid) {
      $status = facebook_status_load($values->facebook_status_sid);
      $pid = $status->pid;
    }
    return facebook_status_display_user_picture(user_load(array('uid' => $pid)));
  }
}