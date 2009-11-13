<?php
// $Id$

/**
 * @file
 *   This file provides a CTools content type containing the author pane.
 */

/**
 * Implementation of hook_ctools_content_types().
 */
function facebook_status_facebook_status_stream_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('Facebook-style Statuses Stream'),
    'icon' => 'icon_user.png',
    'description' => t('A stream of Facebook-style Statuses.'),
    'required context' => new ctools_context_required(t('User'), 'user'),
    'category' => t('User'),
    'defaults' => array('view_name' => 'facebook_status'),
  );
}

/**
 * Implementation of hook_content_type_render().
 */
function facebook_status_facebook_status_stream_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? drupal_clone($context->data) : NULL;
  $block = new stdClass();
  $block->content = t('User information is currently unavailable.');
  if ($account) {
    $block->title = t("Stream");
    $size = variable_get('facebook_status_size_long', 40);
    $block->content = theme('facebook_status_form_display', $account, $size, $conf['view_name']);
  }
  return $block;
}

/**
 * Implementation of hook_content_type_edit_form().
 */
function facebook_status_facebook_status_stream_content_type_edit_form(&$form, &$form_state) {
  if (module_exists('views')) {
    $views = views_get_all_views();
    $list = array('' => t('None'));
    foreach ($views as $name => $view) {
      if ($view->disabled == 0) {
        $list[$name] = $name;
      }
    }
    $form['view_name'] = array(
      '#type' => 'select',
      '#title' => t('View name'),
      '#description' => t('The name of the view to use as the stream. The relevant view should take one argument: the User ID of the user on whose profile this display will be shown. The facebook_status view is strongly recommended.'),
      '#default_value' => $form_state['conf']['view_name'],
      '#options' => $list,
    );
  }
}

/**
 * Implementation of hook_content_type_edit_form_submit().
 */
function facebook_status_facebook_status_stream_content_type_edit_form_submit(&$form, &$form_state) {
  //Copy everything from the defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Implementation of hook_content_type_admin_title().
 */
function facebook_status_facebook_status_stream_content_type_admin_title($subtype, $conf, $context) {
  return t('Stream');
}