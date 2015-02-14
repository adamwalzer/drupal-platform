<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow notices index">

	<div class="header">

		<div class="section">
			<h2>Notices</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="empty">
				There are no notices.
			</div>
		</div>

	</div>

</div>