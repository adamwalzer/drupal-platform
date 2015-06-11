<?php /* 1.4 */ ?>
<?php

if($user->user_type =='parent'){
  print theme('v2_profiles_resource_center_index', theme('image', 'sites/all/themes/cmwn/assets/img/resource-center-coming-soon.jpg'));
}

?>
<div class="block shadow whiteboard index" id="whiteboard-profile-tabs">
	<ul class="header">
		<li class="section">
      <a href="#whiteboard-tab"><h2>Whiteboard</h2></a>
		</li>

		<li class="section">
      <a href="#newsfeed-tab" class="tab-newsfeed"><h2>News Feed</h2></a><span class="call-monitor" title="Call a Monitor"></span>
		</li>
	</ul>

  <div id="whiteboard-tab">
  	<?php print theme('v2_profiles_whiteboard_tab',$data); ?>
  </div>


  <div id="newsfeed-tab">
    <div class="items">
          <?php print views_embed_view('newsfeed', 'block_1');?>
    </div>
  </div>


</div>


