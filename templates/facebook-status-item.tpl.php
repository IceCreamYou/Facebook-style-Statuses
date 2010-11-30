<?php
// $Id$

/**
 * @file
 *   Displays individual status updates.
 *
 * See http://drupal.org/node/226776 for a list of default variables.
 *
 * Other variables available:
 * - $sid: The status message ID
 * - $meta: Information about the context of the status message, like "In response to [recipient]"
 * - $self: Whether the status is an update to the sender's own status
 * - $page: Whether the status is being displayed on its own page
 * - $type: The recipient type
 * - $recipient: The recipient object
 * - $recipient_name: The (safe) recipient name
 * - $recipient_link: A link to the recipient
 * - $recipient_picture: The recipient's picture, if applicable
 * - $sender: The sender object
 * - $sender_name: The (safe) sender name
 * - $sender_link: A themed link to the sender
 * - $sender_picture: The sender's picture
 * - $created: The themed message created time
 * - $message: The themed status message
 * - $links: Status links (edit/delete/respond/share)
 * - $status: The status object
 * - $context: The context array
 *
 * Other modules may add additional variables.
 */
?>
<div id="facebook-status-item-<?php echo $sid; ?>" class="facebook-status-item facebook-status-type-<?php echo $type; ?><?php if ($self): ?> facebook-status-self-update<?php endif; ?><?php if ($page): ?> facebook-status-page<?php endif; ?>">
  <?php if ($sender_picture): ?>
    <div class="facebook-status-sender-picture"><?php echo $sender_picture; ?></div>
  <?php endif; ?>
  <span class="facebook-status-sender"><?php echo $sender_name; ?></span>
  <?php if ($type == 'user' && !$self): ?>
    &raquo; <span class="facebook-status-recipient"><?php echo $recipient_link; ?></span>
  <?php endif; ?>
  <span class="facebook-status-content"><?php echo $message; ?></span>
  <div class="facebook-status-details">
    <span class="facebook-status-time"><?php echo $created; ?></span>
    <?php if ($meta): ?>
      <span class="facebook-status-meta"><?php echo $meta; ?></span>
    <?php endif; ?>
    <?php if ($links): ?>
      <div class="facebook_status_links"><?php echo $links; ?></div>
    <?php endif; ?>
  </div>
</div>
