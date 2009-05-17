<?php
// $Id$

/**
 * @file
 *   Simplifies the Tag Type filter in Views.
 */

/**
 * Changes the form for the Tag Type filter options.
 */
class facebook_status_views_handler_filter_string_type extends views_handler_filter_string {
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#default_value' => $this->value,
      '#options' => array(
        'user' => t('Users'),
        'term' => t('Taxonomy Terms'),
      ),
    );
    if (!isset($form['value'])) {
      // Ensure there is something in the 'value'.
      $form['value'] = array(
        '#type' => 'value',
        '#value' => 'term',
      );
    }
  }
}
