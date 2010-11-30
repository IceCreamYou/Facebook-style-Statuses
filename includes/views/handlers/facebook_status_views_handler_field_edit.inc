<?php
// $Id$

/**
 * @file
 *   Provides an edit link to Views.
 */

/**
 * Field handler to add a field with an edit link.
 */
class facebook_status_views_handler_field_edit extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['pid'] = 'pid';
  }
  function render($values) {
    $status = new stdClass();
    $status->uid = $values->{$this->aliases['uid']};
    $status->pid = $values->{$this->aliases['pid']};
    $status->sid = $values->{$this->field_alias};
    if (_facebook_status_can_edit($status)) {
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/facebook_status.css');
      $q = $_GET['q'];
      if ($q == 'facebook_status/js') {
        $q = 'user';
      }
      return '<span class="facebook_status_edit_delete">'. l(t('Edit'), 'statuses/'. $status->sid .'/edit', array('query' => array('destination' => $q))) .'</span>';
    }
  }
}