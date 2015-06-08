<?php /* 1.4 */ ?>

<div id="v2">
	<?php print l('< Back to School Profile', 'node/' . $data->school->nid, array('html'=>false,'attributes'=>array('class' => 'back-school-profile')));?>
	<div class="block shadow school dashboard">

		<div class="header">

			<div class="section">
				<?php if ($data->school): ?>
				<h2><?php print $data->school->title; ?> - Manage Users</h2>
				<?php endif;?>
			</div>
		</div>

		<?php print drupal_get_form('v2_profiles_school_import'); ?>

		<div class="content" id="school-dashboard-tabs">
			<ul class="menutabs group">
				<li class="">
					<a href="#students-tab" class="tab-students">Students</a>
				</li>
				<li class="">
					<a href="#parents-tab" class="tab-parents">Parents</a>
				</li>
				<li class="">
					<a href="#teachers-tab" class="tab-teachers">Teachers</a>
				</li>
			</ul>

			<div id="students-tab">
				<div class="section">
					<?php print views_embed_view('school_manage_students', 'default', $data->school->nid); ?>
				</div>
			</div>

			<div id="parents-tab">
				<div class="section">
					<?php print views_embed_view('school_manage_parents', 'default', $data->school->nid); ?>
				</div>
			</div>

			<div id="teachers-tab">
				<div class="section">
					<?php print views_embed_view('school_manage_teachers', 'default', $data->school->nid); ?>
				</div>
			</div>

		</div>

	</div>
</div>
