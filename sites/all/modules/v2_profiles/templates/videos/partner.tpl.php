<?php /* 1.4 */ ?>

<div class="block shadow videos index">

	<div class="header">

		<div class="section">
			<h2>Videos</h2>
		</div>

	</div>

	<div class="content">

		<div class="section filter">
			<ul>
				<li class="n1 active" data-n="1"><a href="#">Featured</a></li>
				<li class="n2" data-n="2"><a href="#">All</a></li>
			</ul>
		</div>

		<div class="section panel" data-n="1">
			<?php render_items($data,$data->items->group1); ?>
		</div>

		<div class="section panel" data-n="2" style="display:none;">
			<?php render_items($data,$data->items->group2); ?>
		</div>

	</div>

</div>

<?php function render_items($data,$items) { ?>
	<?php if ($items) { ?>
		<div class="items">
			<?php foreach($items as $item) { ?>
				<div class="item">
					<div class="image">
						<a href="/user/<?php print $data->user->uid; ?>/videos/<?php print $item->nid; ?>">
							<img src="<?php print $item->field_viddler_thumbnail[0]['value']; ?>" width="156" />
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
				</div>
			<?php } ?>
		</div>
	<?php } else { ?>
	<div class="empty">
		There are no videos.
	</div>
	<?php } ?>
<?php } ?>