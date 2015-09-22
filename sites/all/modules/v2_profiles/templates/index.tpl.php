<?php /* 1.4 */ ?>
<?php
//redirect to add child form is session is set
if($data->user->user_type == 'parent') {
	if(isset($_SESSION['cptoken'])) {
		//header("Location: /user/4848/children/add");
	}
}
?>
<?php if ($data->user->user_type == 'child') { ?>
	<?php print v2_profiles_flips_index($data->user->uid); ?>
  <?php if (in_array('can_receive_notices', $user->roles)) { ?>
    <div class="block shadow index feed">
      <div class="header">
        <div class="section">
          <h2>Friend Feed</h2>
        </div>
      </div>
      <div class="content">
        <div class="section friend-feed">
          <div class="items">
            <div class="scroll jscrolldiv" u="<?php print $user->uid;?>"></div>
          </div>
        </div>
      </div>
    </div>

    
    <div class="block shadow index feed">
      <div class="header">
        <div class="section">
          <h2>Flip Feed</h2>
        </div>
      </div>
      <div class="content">
          <div class="section flip-feed">
            <div class="items">
              <div class="scroll jscrolldiv">           
              </div>
            </div>
        </div>
      </div>
    </div>
  <?php } ?>  

	<?php print v2_profiles_whiteboard_index($data->user->uid); ?>

<?php } elseif($data->user->user_type == 'parent' || $data->user->user_type == 'verified-parent' || $data->user->user_type == 'teacher') { ?>

	<?php //print v2_profiles_resource_center_index($data->user->uid, $data->user->user_type); ?>
	<?php print v2_profiles_whiteboard_index($data->user->uid); ?>
	<?php //print v2_profiles_news_index($data->user->uid); ?>
	<?php //print v2_profiles_partners_index($data->user->uid); ?>
<?php } else { ?>
  <?php 
    //print v2_profiles_partners_index($data->user->uid);
    //print $data->user->user_type; 
    print v2_profiles_whiteboard_index($data->user->uid);
  ?>
<?php }?>

  
<?php  //print_r(debug_backtrace()); ?>