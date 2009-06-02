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
  if ($variables['account']->uid != 0) {
    $status = facebook_status_get_status($variables['account']->uid, $variables['account']->uid, 1, -1, FALSE);
    $status = $status[0];
    //There's no reason to show anything if the status is blank. Check to see if
    //it will be blank because theme_facebook_status_item() substitutes a
    //default status if there is none.
    $themed = '';
    if ($status->status_time) {
      $themed = theme('facebook_status_item', $status);
    }
    //Only show the status if the user has permission to see it.
    $facebook_status = '';
    $facebook_status_status = '';
    $facebook_status_time = '';
    if (user_access('view all statuses', $variables['account'])) {
      $facebook_status = $themed;
      $facebook_status_status = check_plain($status->status);
      $facebook_status_time = theme('facebook_status_time', $status->status_time);
    }
    if (!$facebook_status_status) {
      $facebook_status_status = t('does not have a status.');
    }

    //The fully themed status, including the themed username (if settings permit) and the time.
    $variables['facebook_status'] = $facebook_status;
    //Just the status.
    $variables['facebook_status_status'] = $facebook_status_status;
    //The formatted time the status was submitted.
    $variables['facebook_status_time'] = $facebook_status_time;
  }
}