<?php

$cmwn_feed_menu_items['cmwn_feed/flip'] = array(
  'page callback' => 'cmwn_flip_feed',
  'access arguments' => array('access content'),
  'type' => MENU_CALLBACK,
);
 
function cmwn_flip_feed() {//ganked/modified from feed.inc in v2 profile
    
		$items = array();

		$query = "SELECT n.nid, n.uid, td.tid, ctf.field_excerpt_value AS excerpt FROM {node} AS n JOIN {term_node} AS tn ON n.nid = tn.nid JOIN {term_data} AS td ON tn.tid = td.tid and td.vid = 5 JOIN {content_type_feed} AS ctf ON n.nid = ctf.nid JOIN {cmwn_feed_term_weight} cftw on cftw.tid = (select tdd.tid from {term_data} tdd JOIN {term_node} tnn on tnn.tid = tdd.tid AND tdd.vid = 6 where tnn.nid = n.nid limit 1) WHERE n.type = 'feed' AND n.status = 1 and td.tid = 89 order by (cftw.weight * n.created) DESC";
		
    $count_query = "SELECT COUNT(*) FROM (" . $query . ") AS count_query";

		$results = pager_query($query, 13, 0, $count_query);

		while ($result = db_fetch_object($results)) {
			$item = new stdClass();
			$item->excerpt = $result->excerpt;
			$item->nid = $result->nid;
			$item->tid = $result->tid;
			$item->uid = $result->uid;
  		$item->href = url('node/' . $item->nid);
  		$item->src = 
			$items[] = $item;
		}

		?>
		
    <?php foreach ($items as $item) { ?>
      	<div class="item">
      		<span class="image">
      			<img height="42" src="<?php print $item->src; ?>" width="42" />
      		</span>
      		<?php
      			$_excerpt = $item->excerpt;
      			$_excerpt = str_replace('/user/'.$user->uid, '/user', $_excerpt);
      			$_excerpt = preg_replace('/("\/user\/)([0-9]+)(")/i', '/user/'.$friend_feed_user->uid.'/friends/$2/', $_excerpt);
      		?>
      		<span class="message">
      			<?php print $_excerpt; ?>
      		</span>
      	</div>
    <?php } ?>		
    <?php
      print theme('pager', NULL, 10, 0);
      exit;
}