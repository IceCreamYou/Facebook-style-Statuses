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
    $owner = user_load(array('uid' => $values->uid));
    $poster = user_load(array('uid' => $values->pid));
    $status = facebook_status_load($values->sid);
    drupal_alter('facebook_status_render', $status_text, $owner, $poster, $status);
    return $status_text;
  }
}