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
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, 'status');
    $this->query->add_field($this->table_alias, 'uid');
    $this->query->add_field($this->table_alias, 'pid');
    $this->query->add_field($this->table_alias, 'sid');
    $this->query->add_field($this->table_alias, 'status_time');
    $this->add_additional_fields();
  }
  function pre_render($values) {
    $status = new stdClass();
    $status->status = $this->field_alias;
    //Obviously, not the right way to do this...
    $status->pid = drupal_substr($this->field_alias, 0, -6) .'pid';
    $status->sid = drupal_substr($this->field_alias, 0, -6) .'sid';
    $status->uid = drupal_substr($this->field_alias, 0, -6) .'uid';
    $status->status_time = $this->field_alias .'_time';
    $this->status = $status;
  }
  function render($values) {
    $status_fields = $this->status;
    $status = new stdClass();
    $status->uid = $values->{$status_fields->uid};
    $status->pid = $values->{$status_fields->pid};
    $status->sid = $values->{$status_fields->sid};
    $status->status = $values->{$status_fields->status};
    $status->status_time = $values->{$status_fields->status_time};
    $components = facebook_status_item_components($status);
    return $components['status']['#value'];
  }
}