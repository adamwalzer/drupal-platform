<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow notices index">

	<div class="header">

		<div class="section">
			<h2>Awards Notices</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="empty">
				<?php
  				print cmwn_notifications_messaging_get($data->user,cmwn_notifications_award_notices_subjects());
				?>
			</div>
		</div>

	</div>

</div>