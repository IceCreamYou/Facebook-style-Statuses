<?php
// $Id$

/**
 * @file
 *   Filters to statuses where a given user is a participant.
 */

/**
 * Filter handler to select statuses where a given user is a participant.
 */
class facebook_status_views_handler_filter_participant extends views_handler_filter {
  function option_definition() {
    $options = parent::option_definition();
    $options['facebook_status_uid'] = array(
      'default' => '',
      'translatable' => FALSE,
    );
    return $options;
  }
  function options_form(&$form, &$form_state) {
    $form['facebook_status_uid'] = array(
      '#type' => 'textbox',
      '#title' => t('Participant user ID'),
      '#default_value' => $this->options['facebook_status_flag_type'],
      '#required' => TRUE,
    );
  }
  function value_validate($form, &$form_state) {
    if (!is_numeric($form_state['values']['facebook_status_uid'])) {
      form_set_error('facebook_status_uid', t('The specified user ID must be numeric.'));
    }
  }
  function query() {
    $this->query->add_where(
      $this->options['group'],
      "($this->table.sender = %d OR $this->table.recipient = %d) AND $this->table.type = 'user'",
      $this->options['facebook_status_uid'],
      $this->options['facebook_status_uid']
    );
  }
}
