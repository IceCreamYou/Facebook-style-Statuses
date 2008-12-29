// $Id$

===========
== Notes ==
===========

Patches and bug reports welcome at http://drupal.org/project/facebook_status.

=============
== Summary ==
=============

This module provides each user with a Facebook-style status.  This is a 
textfield where users can type what they're doing or thinking at that moment.  

The user's status is available for display in several places.  In most cases, 
the module will decide whose status to show based on these rules: If a status 
appears on a profile page, it displays the status of the owner of the profile. 
If it appears on a node, it displays the status of the owner of the node.  If 
it appears anywhere else, it displays the status of the currently logged-in 
user.

Two permissions are provided: 'edit own facebook_status' and 'edit all 
facebook_status.'  Any time a user has permission to edit a status that is 
visible in the Facebook Status or Facebook Status Individual User blocks, that
user will be able to access the status update form.  If enabled on the module's
settings page, the form can be automatically shown and hidden via AJAX when a 
user with permission to see the form clicks on the status text.  The default 
text that appears in the textfield is the user's latest status.

There is also support for the Activity module.  This allows a more Facebook
-style "mini-feed" if desired, and so allows status updates to be displayed 
with updates from other parts of the site.  Though significantly less useful, 
support for the Token module (required by Activity) is also available.

This module further integrates with Advanced Forum and User Relationships.  In 
Advanced Forum-themed comments, the user's status will appear beneath the 
user's picture.  For User Relationships, a block is provided to display the 
recent status updates of users with whom the current user has a relationship.  
In addition, translation strings (integration with i18n) are comprehensively 
available.

============
== Blocks ==
============

http://www.example.com/?q=admin/build/block

First and foremost, this module adds a block labeled "Facebook Status" to the 
site.  This block automatically decides which status to display based on the 
rules specified above.  This is the block that users usually use to update 
their statuses.

Secondly, a "Facebook Status Recent Updates" block is available.  This lists 
the latest status updates from all users on the site, but only shows one update
per user.

Third is the "Facebook Status User Update History" block.  This lists the 
latest updates from a single user, determined based on where the block appears.

Fourth, the "Facebook Status Individual User" block works just like the 
Facebook Status block, but it only displays the status for one user (specified 
on the block configuration form).  This is useful for personal sites with only
one user.

Lastly, if the User Relationships module is enabled, a "Facebook Status UR 
Recent Updates" block is available.  This does the same thing as the "Facebook 
Status Recent Updates" block except that it only shows updates from users with 
whom the current user has a relationship.  The relationship type can be set on 
the module's settings page.

==============
== Settings ==
==============

http://www.example.com/?q=admin/settings/facebook_status

The settings page for this module is very comprehensive without being 
overwhelming.  It allows you to customize nearly everything about this module. 
Most of the available settings involve changing the length of statuses or the 
number of statuses that show up in various blocks.

This module provides what is known as "Facebook Mode," which can be enabled or 
disabled on the settings page.  Facebook Mode is enabled by default, and 
appends the relevant user's username to the front of the status.  That means 
users' statuses will be in the format "IceCreamYou is happy."  With Facebook 
Mode off, the module becomes a place for thought blurbs: for example, it could 
be used as a quote of the day of sorts.

This module does not, and will not, sync Drupal status updates with Facebook's,
and it is not affiliated with Facebook in any way.


=====================
== Development/API ==
=====================

This module's code is documented and styled in the Drupal Way, for any 
developers that would like to take a look.

For anyone who doesn't want to delve that deeply, this module provides simple 
functions you can use to take advantage of its functionality from anywhere you 
can use PHP.  For more information, see the function descriptions in
facebook_status.module.

(A) facebook_status_get_status($fbs_uid, $num_results)
    Returns an array of arrays. Each sub-array contains information about a 
single status update: the status itself, the timestamp, the user's UID, and the
user's username. If no UID is passed in $fbs_uid, facebook_status figures out 
which one to use based on what page the function is called from. If the UID 
passed is -1, this function returns results for all users, but only includes 
one status update per user. If the UID passed is less than -1, this function 
returns all status updates. $num_results controls the number of status updates 
returned. If it is not specified, it defaults to 1; if it is passed as zero, 
there is no limit on the number of status updates returned.
    Developers can also pass an array of UIDs in as $fbs_uid to get the latest 
status updates for those users.  In this case, it is possible to specify a 
negative value for $num_results, which cause only one update for each user to 
be returned instead of all of them; the maximum number of results returned will
be the reciprocal of $num_results.

(B) facebook_status_display_form($uid)
    Prints the status update form. Developers could use this, for instance, if 
they wanted to create a separate block for the user's status and for the status
update form. If no UID is passed, it decides which one to use automatically.  
Output is fully themed like the Facebook Status block.

(C) facebook_status_get_rel_status($ur_rtid, $number, $grouping)
    Returns the latest status updates from users with whom the current user has
a relationship in the same form as facebook_status_get_status. If $grouping is 
TRUE, only one status update is returned per user; if FALSE, all statuses are 
returned for the relevant users. If $ur_rtid is -2 or not passed, this function
uses the default relationship specified on the Facebook Status settings page. 
If it is -1, all relationship types will be used.  It can also be an array with
RTIDs as keys, if multiple relationship types are needed. $number controls the 
number of statuses returned; if it is not passed, it defaults to the setting on
the Facebook Status settings page.

(D) facebook_status_list_render($fbs_list)
    Returns themed HTML for a list of status updates.  $fbs_list is an array in
the form returned by facebook_status_get_status().


==================
== Installation ==
==================

   1. Install this module as usual (FTP the files to sites/all/modules, enable 
        at admin/build/modules).  See http://drupal.org/node/70151 for help.

   2. If you want, go to admin/settings/facebook_status to change some minor 
        settings. The defaults should work for most people.

   3. Go to admin/user/access#facebook_status and set the permissions there. 
        Note that anyone who can edit statuses (whether their own or 
        everyone's) can also see everyone's status (because what fun is it if 
        you can only see your own?). If you don't want this behavior you can 
        use the functions (explained above) to build custom blocks so you have 
        more fine-grained control.

   4. Go to admin/build/block and put the blocks in the regions you want them.

   5. Still on admin/build/block, configure the settings for each of the 
        Facebook Status blocks. Set the blocks to only show up for users who 
        you want to be able to see anyone's status.

   6. On the block configuration pages, scroll to the bottom and set where you 
        want the blocks to show up. The most common configuration is to have 
        them show up on user pages; to do this, choose the PHP option and enter
        the code below.
          <?php
            return arg(0) == 'user' && is_numeric(arg(1)) && !arg(2);
          ?>
        In order to get a block to show up only on a user's own profile, use 
        this code instead:
          <?php
            global $user;
            return arg(0) == 'user' && arg(1) == $user->uid && !arg(2);
          ?>


===========
== Links ==
===========

Visit the module page for more information and details about upcoming features.

Module Page: http://drupal.org/project/facebook_status
User Relationships: http://drupal.org/project/user_relationships
Activity: http://drupal.org/project/activity
Token: http://drupal.org/project/token

Enable Module: http://example.com/?q=admin/build/modules
Enable Blocks: http://example.com/?q=admin/build/block
Settings Page: http://example.com/?q=admin/settings/facebook_status
Set Permissions: http://example.com?q=admin/user/access