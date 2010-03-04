<?php
// $Id$

/**
 * @file
 *   Provides an edit link to Views.
 */

/**
 * Field handler to add a field with an edit link.
 */
class facebook_status_views_handler_field_delete extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field($this->table_alias, 'sid');
    $this->query->add_field($this->table_alias, 'uid');
    $this->query->add_field($this->table_alias, 'pid');
    $this->add_additional_fields();
  }
  function pre_render($values) {
    $status = new stdClass();
    $status->sid = $this->field_alias;
    //Obviously, not the right way to do this...
    $status->pid = str_replace('sid', 'pid', $this->field_alias);
    $status->uid = str_replace('sid', 'uid', $this->field_alias);
    $this->status = $status;
  }
  function render($values) {
    $status_fields = $this->status;
    $status = new stdClass();
    $status->uid = $values->{$status_fields->uid};
    $status->pid = $values->{$status_fields->pid};
    $status->sid = $values->{$status_fields->sid};
    if (_facebook_status_can_edit($status, TRUE)) {
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $q = $_GET['q'];
      if ($q == 'facebook_status/js') {
        $q = 'user';
      }
      return '<span class="facebook_status_edit_delete">'. l(t('Delete'), 'statuses/'. $status->sid .'/delete', array('query' => array('destination' => $q))) .'</span>';
    }
  }
}