<?php
// $Id$

/**
 * @file
 *   Handling for the recipient's name.
 */

/**
 * Allows linking to the recipient of the status.
 */
class facebook_status_views_handler_field_recipient extends views_handler_field_user {
  function render($values) {
    $account = _facebook_status_user_load($values->{$this->field_alias});
    if (!empty($this->options['link_to_user'])) {
      return theme('username', $account);
    }
    return check_plain($account->name);
  }
}
