<?php
// $Id$

/**
 * @file
 *   Formats the status comment update form in Views.
 */

/**
 * Field handler to add the status comment update form.
 */
class fbssc_views_handler_field_comment_box extends views_handler_field {
  function render($values) {
    return theme('fbssc_form_display', $values->facebook_status_sid, TRUE, TRUE);
  }
}