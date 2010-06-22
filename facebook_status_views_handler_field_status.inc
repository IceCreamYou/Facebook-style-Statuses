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
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['pid'] = 'pid';
    $this->additional_fields['sid'] = 'sid';
    $this->additional_fields['status_time'] = 'status_time';
  }
  function render($values) {
    $status = new stdClass();
    $status->uid = $values->{$this->aliases['uid']};
    $status->pid = $values->{$this->aliases['pid']};
    $status->sid = $values->{$this->aliases['sid']};
    $status->status = $values->{$this->field_alias};
    $status->status_time = $values->{$this->aliases['status_time']};
    $components = facebook_status_item_components($status);
    return $components['status']['#value'];
  }
}