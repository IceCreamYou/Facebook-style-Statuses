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
  function option_definition() {
    $options['facebook_status_tags_type'] = array(
      'default' => array(),
      'translatable' => FALSE,
    );
    return $options;
  }
  function options_form(&$form, &$form_state) {
    $opt = array('user' => t('Users'));
    if (module_exists('taxonomy')) {
      $opt['term'] = t('Terms');
    }
    $options = $this->options;
    $form['facebook_status_tags_type'] = array(
      '#title' => t('Tag types'),
      '#type'  => 'checkboxes',
      '#options' => $opt,
      '#default_value' => $options['facebook_status_tags_type'],
      '#description' => t('You probably want to choose only one tag type.'),
    );
  }
  function query() {
    $options = $this->options['facebook_status_tags_type'];
    $types = array();
    foreach ($options as $type => $val) {
      if ($val) {
        $types[] = $type;
      }
    }
    if (count($types) > 1) {
      $query = "type IN ('". implode("', '", $types) ."')";
    }
    else if (count($types) == 1) {
      $query = "type = '". $types[0] ."'";
    }
    else {
      return;
    }
    $this->query->add_where(0, $query);
  }
}