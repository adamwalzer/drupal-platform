<?php
  $u = $data->getBaseProfile();
  $user_data = unserialize($u->data);
  //print_r($user_data['user_type']);
  switch($user_data['user_type']):?>
<?php case 'parent':?>
<?php print '<div class="block shadow  parent-resource-center">'.theme('image','sites/all/themes/cmwn/assets/img/resource-center-coming-soon.jpg').'</div>'; ?>
<?php break; ?>
<?php case 'teacher':?>
<iframe class="block shadow" src="http://demoai.changemyworldnow.com?uid=<?php print $data->uid?>&BrowseType=Teacher" width="100%" height="735px" frameborder="no" scrollbars
	="none" scrolling="no"></iframe>
<?php break;?>

<?php endswitch;?>