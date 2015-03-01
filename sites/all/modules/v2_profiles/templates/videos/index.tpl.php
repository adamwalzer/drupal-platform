<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow videos index">

	<div class="header">

		<div class="section">
			<h2>My Media</h2>
			<input id="profile-media-search" placeholder="Search Media" />
		</div>

	</div>

	<div class="content">

		<div class="section filter">
			<ul>
				<li class="n1 active" data-n="1"><a href="#">All</a></li>
				<li class="n6" data-n="6"><a href="#">My<br/>Photos</a></li>
				<li class="n2" data-n="2"><a href="#">My<br/>Videos</a></li>
				<li class="n4" data-n="4"><a href="#">My<br/>Friends</a></li>
				<li class="n3" data-n="3"><a href="#">Change My<br/>World Now</a></li>
				<li class="n7" data-n="7"><a href="#">Project<br/>Album</a></li>
				<?php //<li class="n5" data-n="5"><a href="#">My School</a></li> ?>
			</ul>
		</div>

		<div class="section panel" data-n="1">
  		<div class="button add-media">Add Media</div>
			<?php render_items($data,$data->items->group1); ?>
		</div>

		<div class="section panel" data-n="6" style="display:none;">
  		<div class="button add-media">Add Media</div>
			<?php render_items($data,$data->items->group6); ?>
		</div>

		<div class="section panel" data-n="2" style="display:none;">
  		<div class="button add-media">Add Media</div>
			<?php render_items($data,$data->items->group2); ?>
		</div>

		<div class="section panel" data-n="4" style="display:none;">
			<?php render_items($data,$data->items->group4); ?>
		</div>

		<div class="section panel" data-n="3" style="display:none;">
  		<div class="button add-media">Add Media</div>
			<?php render_items($data,$data->items->group3); ?>
		</div>

    <?php /*
		<div class="section panel" data-n="5" style="display:none;">
  		<div class="button add-media">Add Media</div>
			<?php render_items($data,$data->items->group5); ?>
		</div>
    */ ?>
		<div class="section panel" data-n="7" style="display:none;">
  		<a href="/user/<?php print $data->user->uid; ?>/flips/browse" class="button discover-flips">Discover Other Action Items</a>
			<?php render_items($data,$data->items->group7); ?>
		</div>

	</div>

</div>

<?php function render_items($data,$items) { ?>
	<?php if ($items) { ?>
		<div class="items">
			<?php foreach($items as $item) { ?>
			<?php render_item_by_type($data,$item);?>
			<?php } ?>
		</div>
	<?php } else { ?>
	<div class="empty">
		There is no media in this section.
	</div>
	<?php } ?>
<?php } ?>


<?php function render_item_by_type($data,$item){
	//print $item->type;
	switch($item->type){
		case 'video': ?>
			<div class="item">
				<div class="image">
					<a href="/user/<?php print $data->user->uid; ?>/videos/<?php print $item->nid; ?>" class="ext-video">
						<img src="<?php print $item->field_viddler_thumbnail[0]['value']; ?>" width="156" />
						<?php print theme('image','sites/all/themes/cmwn/assets/img/media-play-overlay.png', 'play', '', array('class'=>'play-btn')); ?>
					</a>
				</div>
				<div class="name">
					<a href="/user/<?php print $data->user->uid; ?>/videos/<?php print $item->nid; ?>">
						<?php print $item->title; ?>
					</a>
				</div>
				<div class="user">
					By
					<?php $_user = user_load($item->uid); ?>
					<a href="/user/<?php print $_user->uid; ?>">
						<?php print $_user->name; ?>
					</a>
				</div>
				<div class="date">
					<?php print date('m/d/Y',$item->created); ?>
				</div>
			</div><?php
			break;

		case 'whiteboard':?>
			<div class="item">

				<div class="image">

						<?php print theme('imagecache', 'media-project', $item->field_image[0]['filepath']); ?>

				</div>

				<div class="name">

						<h3><?php print $item->field_image[0]['filename']; ?></h3>

				</div>
				<div class="user">
					By
					<?php $_user = user_load($item->uid); ?>
					<a href="/user/<?php print $_user->uid; ?>">
						<?php print $_user->name; ?>
					</a>
				</div>
				<div class="date">
					<?php print date('m/d/Y',$item->created); ?>
				</div>
			</div><?php

			break;


			case 'flip_milestone':
  			  $submission = webform_get_submission($item->nid, $item->sid);
          $fid = $submission->data[$item->cid]['value'][0];
          //print $fid;
          //$file = file_load($fid);
          @$file = db_fetch_object(db_query("SELECT * FROM {files} WHERE fid = %d", $fid));
          if(!$file){

          }else{?>
						<div class="item">
							<div class="image">
									<?php print theme('imagecache', 'media-project', $file->filepath);  ?>
							</div>
							<div class="name">
									<h3><?php print $item->title; ?></h3>
							</div>
							<div class="user">
								By
								<?php $_user = user_load($item->uid); ?>
								<a href="/user/<?php print $_user->uid; ?>">
									<?php print $_user->name; ?>
								</a>
							</div>
							<div class="date">
								<?php print date('m/d/Y',$item->created); ?>
							</div>
						</div>
          <?php
        }

			break;
	 }
}
