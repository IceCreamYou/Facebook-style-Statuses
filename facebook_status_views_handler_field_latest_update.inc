<?php

/**
 * @file
 *   Allows showing users' most recent status in Views.
 */

/**
 * Field handler to provide the most recent status update.
 */
class facebook_status_views_handler_field_latest_update extends views_handler_field {

  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = array('table' => 'users', 'field' => 'uid');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['uid'];
  }

  function render($values) {
    $status = facebook_status_get_status($values->uid, 1, -1, TRUE);
    return $status[0]->status;
  }
}