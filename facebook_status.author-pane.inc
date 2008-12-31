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
    //TRUE includes the themed username; FALSE is just the status.
    $variables['facebook_status'] = facebook_status_advf($variables['account'], TRUE);
    $variables['facebook_status_status'] = facebook_status_advf($variables['account'], FALSE);
  }
}