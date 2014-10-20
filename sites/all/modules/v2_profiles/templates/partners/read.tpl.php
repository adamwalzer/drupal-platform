<?php /* 1.4 */ ?>

<div class="block shadow partners index">

	<div class="header">

		<div class="section">
			<h2>Partner</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">

			<div class="cms" style="background:url(<?= '/'.$data->item->field_logo[0]['filepath']?>) 0px 0px no-repeat;">
				<p><?php print strip_tags($data->item->body); ?></p>
			</div>

		</div>

	</div>

</div>

<?php print v2_profiles_videos_partner($data->item->nid); ?>

<?php print v2_profiles_flips_partner($data->item->nid); ?>