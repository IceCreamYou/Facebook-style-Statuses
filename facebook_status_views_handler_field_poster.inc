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
    $account = _facebook_status_user_load($values->{$this->field_alias});
    if (!empty($this->options['link_to_user'])) {
      return theme('username', $account);
    }
    return check_plain($account->name);
  }
}