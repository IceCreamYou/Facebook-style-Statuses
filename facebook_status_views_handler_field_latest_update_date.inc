<?php

/**
 * @file
 *   Allows showing the posted time of users' most recent status in Views.
 */

/**
 * Field handler to provide the time for the most recent status update.
 */
class facebook_status_views_handler_field_latest_update_date extends views_handler_field_date {

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
    $value = $status[0]->status_time;
    $format = $this->options['date_format'];
    if ($format == 'custom' || $format == 'time ago' || $format == 'raw time ago') {
      $custom_format = $this->options['custom_date_format'];
    }

    switch ($format) {
      case 'raw time ago':
        return $value ? format_interval(time() - $value, is_numeric($custom_format) ? $custom_format : 2) : theme('views_nodate');
      case 'time ago':
        return $value ? t('%time ago', array('%time' => format_interval(time() - $value, is_numeric($custom_format) ? $custom_format : 2))) : theme('views_nodate');
      case 'custom':
        return $value ? format_date($value, $format, $custom_format) : theme('views_nodate');
      default:
        return $value ? format_date($value, $format) : theme('views_nodate');
    }

  }
}