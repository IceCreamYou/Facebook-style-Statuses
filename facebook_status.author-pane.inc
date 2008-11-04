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
  $account_id = $variables['account']->uid;
  if ($account_id != 0) {
    $variables['facebook_status'] = facebook_status_advf($account_id);
  }
}