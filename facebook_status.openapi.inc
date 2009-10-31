<?php
// $Id$

/**
 * @file
 *   Computes what to show on the OpenAPI page.
 */

/**
 * Handles the Open API.
 */
function _facebook_status_openapi() {
  drupal_set_header('Content-Type: text/html; charset: utf-8');
  if (!flood_is_allowed('facebook_status_flood_user', variable_get('facebook_status_flood_user', 60))) {
    echo t('You have exceeded the maximum number of open-API accesses per hour. Please try again later.');
  }
  flood_register_event('facebook_status_flood_user');
  $name = $_GET['name'];
  $count = $_GET['count'];
  $type = $_GET['type'];
  $format = $_GET['format'];
  if ($format != 'json' && $format != 'xml' && $format != 'short' && $format) {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo t('invalid "format" parameter');
    return;
  }
  if ((!is_numeric($count) || round($count) != $count || $count < 1 || $count > 25) && $format != 'short' && $count) {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo t('"count" parameter must be a positive integer no larger than 25');
    return;
  }
  if (($type == 'tag' || $type == 'user' || $type == 'userref') && !$name) {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo t('if "type" is "tag" or "user" or "userref" you must use the "name" parameter as well');
    return;
  }
  if ($type && $type != 'tag' && $type != 'user' && $type != 'public' && $type != 'userref' && $type != 'trend') {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo t('invalid "type" parameter');
    return;
  }
  if (($type == 'tag' || $type == 'trend') && (!module_exists('facebook_status_tags') || !module_exists('taxonomy'))) {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo 'invalid "type" parameter';
    return;
  }
  if ($type == 'userref' && !module_exists('facebook_status_tags')) {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo t('invalid "type" parameter');
    return;
  }
  if ($type == 'trend' && $name && $name != 'day' && $name != 'week' && $name != 'month' && $name != 'year' && $name != 'all') {
    drupal_set_header('HTTP/1.x 400 Bad Request');
    echo t('if the "name" parameter is specified with type "trend" then it must be one of "day" "week" "month" "year" "all"');
    return;
  }
  if (!$type && !$name) {
    $type = 'public';
  }
  if (!$type && $name) {
    $type = 'user';
  }
  if (!$count || $format == 'short') {
    $count = 1;
  }
  if (!$format) {
    $format = 'short';
  }
  if ($type == 'user' || $type == 'userref') {
    $account = user_load(array('name' => $name));
    if (!$account->uid) {
      drupal_set_header('HTTP/1.x 400 Bad Request');
      echo 'invalid name';
      return;
    }
  }

  $statuses = array();
  $terms = array();
  switch ($type) {
    case 'tag':
      $statuses = facebook_status_tags_get_statuses($name, 'term', $count);
      break;
    case 'userref':
      $statuses = facebook_status_tags_get_statuses($name, 'user', $count);
      break;
    case 'user':
      $statuses = facebook_status_get_status($account->uid, $account->uid, $count, 0, TRUE);
      break;
    case 'public':
      $statuses = facebook_status_get_statuses(array(), array(), $count, FALSE);
      break;
    case 'trend':
      $terms = facebook_status_tags_popular_terms($count, $name);
      break;
  }
  if ((empty($statuses) && $type != 'trend') || (empty($terms) && $type == 'trend')) {
    drupal_set_header('HTTP/1.x 204 No Content');
    echo t('no statuses match your criteria');
    return;
  }
  $clean = array();
  $xml = '';
  foreach ($statuses as $status) {
    $array = array(
      'text' => check_plain($status->status),
      'time' => $status->status_time,
      'sid' => $status->sid,
      'uid' => $status->uid,
    );
    $xml .= '
  <status>
'. format_xml_elements($array) .'
  </status>';
    $clean[] = $array;
  }
  foreach ($terms as $term) {
    $array = array(
      'name' => check_plain($term->name),
      'tid' => $term->tid,
      'popularity' => $term->popularity,
    );
    $xml .= '
  <term>
'. format_xml_elements($array) .'
  </term>';
    $clean[] = $array;
  }
  if ($format == 'xml') {
    drupal_set_header('HTTP/1.x 200 OK');
    drupal_set_header('Content-Type: application/xml; charset=utf-8');
    echo '<?xml version="1.0" encoding="UTF-8"?>
';
    if ($type != 'trend') {
      echo '<statuses>'. $xml .'
</statuses>';
    }
    else {
      echo '<terms>'. $xml .'
</terms>';
    }
  }
  elseif ($format == 'json') {
    drupal_json($clean);
  }
  elseif ($format == 'short') {
    drupal_set_header('HTTP/1.x 200 OK');
    if ($type != 'trend') {
      echo $clean[0]['text'];
    }
    else {
      echo $clean[0]['name'];
    }
  }
}