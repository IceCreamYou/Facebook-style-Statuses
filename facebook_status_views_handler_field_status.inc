<?php
// $Id$

/**
 * @file
 *   Formats statuses in Views.
 */

/**
 * Field handler to provide the most recent status update.
 */
class facebook_status_views_handler_field_status extends views_handler_field {
  function render($values) {
    $status_text = _facebook_status_run_filter($values->facebook_status_status);
    if (variable_get('facebook_status_nl2br', 0)) {
      $status_text = nl2br($status_text);
    }
    $owner = user_load(array('uid' => $values->uid));
    $poster = user_load(array('uid' => $values->pid));
    $status = facebook_status_load($values->facebook_status_sid);
    drupal_alter('facebook_status_render', $status_text, $owner, $poster, $status);
    return $status_text;
  }
}