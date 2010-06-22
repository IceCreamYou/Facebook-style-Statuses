<?php
// $Id$

/**
 * @file
 *   Handling for cross-posting.
 */

/**
 * Shows either the status owner (if the status was posted to one's own profile)
 * or the status owner and status poster (if the status was posted elsewhere).
 * Also shows the user picture.
 */
class facebook_status_views_handler_field_cross_pic extends views_handler_field {
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
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
  }
  function render($values) {
    $uid = $values->{$this->aliases['uid']};
    $pid = $values->{$this->field_alias};
    $options = $this->options;
    if (isset($uid) && $pid == $uid) {
      $account = _facebook_status_user_load($uid);
      if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
        $account->imagecache_preset = $options['imagecache_preset'];
      }
      return t('!picture !user', array('!picture' => facebook_status_display_user_picture($account), '!user' => theme('username', $account)));
    }
    else {
      $poster = _facebook_status_user_load($pid);
      $owner = _facebook_status_user_load($uid);
      if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
        $poster->imagecache_preset = $options['imagecache_preset'];
        $owner->imagecache_preset = $options['imagecache_preset'];
      }
      $args = array('!poster' => theme('username', $poster), '!owner' => theme('username', $owner));
      $args['!poster-picture'] = facebook_status_display_user_picture($poster);
      $args['!owner-picture'] = facebook_status_display_user_picture($owner);
      return t('!poster-picture !poster &raquo; !owner-picture !owner', $args);
    }
  }
}