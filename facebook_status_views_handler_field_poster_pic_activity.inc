<?php
// $Id$

/**
 * @file
 *   Handling for the poster's picture in Activity Views.
 */

/**
 * Shows the profile picture for the user who posted the status.
 */
class facebook_status_views_handler_field_poster_pic_activity extends views_handler_field {
  function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['eid'] = array('table' => 'activity', 'field' => 'eid');
    $this->additional_fields['type'] = array('table' => 'activity', 'field' => 'type');
  }
  function option_definition() {
    $options = parent::option_definition();
    if (module_exists('imagecache_profiles')) {
      $options['imagecache_preset'] = array(
        'default' => variable_get('user_picture_imagecache_profiles_default', ''),
        'translatable' => FALSE,
      );
    }
    return $options;
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    if (module_exists('imagecache_profiles')) {
      $presets = imagecache_presets();
      $opt = array('' => '');
      foreach ($presets as $preset) {
        $opt[$preset['presetname']] = check_plain($preset['presetname']);
      }
      $options = $this->options;
      $form['imagecache_preset'] = array(
        '#title' => t('Imagecache preset'),
        '#type'  => 'select',
        '#options' => $opt,
        '#default_value' => $options['imagecache_preset'],
      );
    }
  }
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
  function render($values) {
    if ($values->{$this->aliases['type']} == 'facebook_status') {
      $sid = $values->{$this->aliases['eid']};
      $status = facebook_status_load($sid);
      $account = _facebook_status_user_load($status->pid);
    }
    else {
      $account = _facebook_status_user_load($values->{$this->field_alias});
    }
    $options = $this->options;
    if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
      $account->imagecache_preset = $options['imagecache_preset'];
    }
    return facebook_status_display_user_picture($account);
  }
}