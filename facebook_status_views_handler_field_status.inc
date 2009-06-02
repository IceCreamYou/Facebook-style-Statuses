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
    $output = _facebook_status_run_filter($values->facebook_status_status);
    $functions = module_invoke_all('facebook_status_render', user_load(array('uid' => $values->uid)), $output, TRUE);
    foreach ($functions as $function => $args) {
      $output = call_user_func_array($function, array_merge(array($output), $args));
    }
    return $output;
  }
}