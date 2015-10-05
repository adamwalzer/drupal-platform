<?php /* 1.4 */ ?>

<?php foreach ($data->items as $item) { ?>

	<div class="block profile parent-child">

		<?php print v2_profiles_avatars_index($item->uid); ?>

		<?php print v2_profiles_flips_index($item->uid, 5, 5); ?>
    <?php $arg3 = arg(3);print (strlen($arg3)>0)?v2_profiles_friends_browse($item->uid, 11):''; ?>
	</div>

  <div class="block trigger1-target" style="clear:both;display:none;">

    <?php print v2_profiles_friends_browse($item->uid); ?>

  </div>


	<?php if (!$data->teaser) { ?>

		<div class="parent-child-whiteboard">
      <?php print v2_profiles_whiteboard_index($item->uid); ?>
    </div>

	<?php } ?>

<?php } ?>
