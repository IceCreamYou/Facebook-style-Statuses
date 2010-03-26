<?php
// $Id$

/**
 * @file
 *   This file provides a preprocess function for the author pane used by
 *   Advanced Forum and Advanced Profile Kit.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function facebook_status_preprocess_author_pane(&$variables) {
  $variables += array(
    'facebook_status' => '',
    'facebook_status_status' => t('does not have a status.'),
    'facebook_status_time' => '',
  );
  if ($variables['account']->uid == 0 || !user_access('view all statuses')) {
    return;
  }
  $statuses = facebook_status_get_status($variables['account']->uid, $variables['account']->uid, 1, -1, FALSE);
  if (!is_array($statuses) || empty($statuses)) {
    return;
  }
  $status = $statuses[0];
  //Show nothing if the status is blank.
  if ($status->status_time) {
    //The fully themed status, including the themed username (if settings permit) and the time.
    $variables['facebook_status'] = theme('facebook_status_item', $status);
    //Just the status.
    $variables['facebook_status_status'] = check_plain($status->status);
    //The formatted time the status was submitted.
    $variables['facebook_status_time'] = theme('facebook_status_time', $status->status_time);
  }
}