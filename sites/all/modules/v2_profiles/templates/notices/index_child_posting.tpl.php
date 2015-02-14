<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow notices index">

	<div class="header">

		<div class="section">
			<h2><?php print $data->child->name;?>'s Posting Notices</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="empty">
				<?php
  				print cmwn_notifications_messaging_get($data->user,'Inappropriate Content', $data->child->uid);
				?>
			</div>
		</div>

	</div>


<div class="header">

		<div class="section">
			<h2><?php print $data->child->name;?>'s Award Notices</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="empty">
				<?php
  				print cmwn_notifications_messaging_get($data->user,'Flip Award', $data->child->uid);
				?>
			</div>
		</div>

	</div>


</div>