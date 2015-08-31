<?php 
$user = user_load(arg(1));
$guser = false;
if ($user) {
  $guser = GenericUser::castAs($user);
}
$parent = ParentUser::canHydrate($user) ? ParentUser::castAs($user) : false;
?>
<ul>
  <li><?php echo l('Pick Avatar', 'user/'.arg(1).'/edit-profile', array('query' => drupal_get_destination()))?></li>
  <li><?php echo l('Change Password', 'user/'.arg(1).'/edit/password', array('query' => drupal_get_destination()))?></li>
  <li><?php echo $guser?l('Personal Information', 'node/'.$guser->getBaseProfile()->nid.'/edit', array('query' => drupal_get_destination())):''?></li>
  <?php if ($parent) :?>
  <li><?php echo l('Add My Child', 'user/'.arg(1).'/add-child', array('query' => drupal_get_destination()))?></li>
  <?php endif; ?>
  <li><?php echo l('Delete My Account', 'user/'.arg(1).'/delete-profile')?></li>
</ul>