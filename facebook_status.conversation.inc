<?php
// $Id$

/**
 * @file
 *   Handles the conversation view.
 */

/**
 * Builds a page with a conversation view. A form to post a message to the other
 * user's profile may be at the top. If it is and if the user has JavaScript
 * enabled in their browser, the view will update via AJAX when the message is
 * submitted.
 */
function _facebook_status_conversation() {
  if (!module_exists('views')) {
    watchdog('facebook_status', 'Someone attempted to access the conversation page, which does not exist unless the Views module is installed.');
    drupal_not_found();
  }
  global $user;
  $view = 'facebook_status_cross_post';
  $args = explode(',', arg(2));
  if (in_array($user->name, $args) || in_array($user->uid, $args) || count($args) === 1) {
    if (count($args) === 1 && ($args[0] == $user->uid || $args[0] == $user->name)) {
      drupal_not_found();
      return;
    }
    elseif (count($args) === 1) {
      if (is_numeric($args[0])) {
        $account = user_load(array('uid' => $args[0]));
      }
      else {
        $account = user_load(array('name' => $args[0]));
      }
    }
    else {
      if (is_numeric($args[0])) {
        $key = array_search($user->uid, $args);
        if ($key === 1) {
          $key = 0;
        }
        elseif ($key === 0) {
          $key = 1;
        }
        $account = user_load(array('uid' => $args[$key]));
      }
      else {
        $key = array_search($user->name, $args);
        if ($key === 1) {
          $key = 0;
        }
        elseif ($key === 0) {
          $key = 1;
        }
        $account = user_load(array('name' => $args[$key]));
      }
    }
    if (user_access('post on all profiles') && $account->uid) {
      return theme('facebook_status_form_display', $account, variable_get('facebook_status_size_long', 40), $view, arg(2));
    }
    elseif ($account->uid) {
      return views_embed_view($view, 'default', arg(2));
    }
    drupal_not_found();
    return;
  }
  if (is_numeric($args[0])) {
    $account1 = user_load(array('uid' => $args[0]));
    $account2 = user_load(array('uid' => $args[1]));
  }
  else {
    $account1 = user_load(array('name' => $args[0]));
    $account2 = user_load(array('name' => $args[1]));
  }
  if ($account1->uid && $account2->uid) {
    return views_embed_view($view, 'default', arg(2));
  }
  drupal_not_found();
}