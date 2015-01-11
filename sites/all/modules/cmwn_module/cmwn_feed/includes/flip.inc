<?php

$cmwn_feed_menu_items['cmwn_feed/flip'] = array(
  'page callback' => 'cmwn_flip_feed',
  'access arguments' => array('access content'),
  'type' => MENU_CALLBACK,
);

  
function cmwn_feed_flip_queries_list(){
  $feed_queries = array(
    'brand partner released new flip',
    'new brand partner',
    'special edition flip',

  );  
  return $feed_queries;
}

function cmwn_feed_flip_query_weights(){
  
  $flip_feed_queries = cmwn_feed_flip_queries_list();
  
  $flip_feed_weights = db_placeholders(cmwn_feed_flip_queries_list($flip_feed_queries));
  
  $result = db_query("SELECT query_name, weight FROM {cmwn_feed_weight} cfw where query_name in ($flip_feed_weights)", $flip_feed_queries);
  
  $weights = array();
  
  while ($row = db_fetch_object($result)) {
    $weights[$row->query_name] = (float)$row->weight;
  }     
  
  return $weights;

}


function cmwn_flip_feed() {
    
		$items = array();
    global $user;
    
    if($user->uid < 1){
      exit;
    }
    
    $weights = cmwn_feed_flip_query_weights();
		
    $feed_queries['brand partner released new flip'] =  "(SELECT 
      	    CONCAT('<a href=\"/node/', bpn.nid,'\">', bpn.title,'</a> has released a new flip action item called <em><a href=\"/node/', fn.nid,'\">' , fn.title , '</a></em>' ) as excerpt, 
      	    f.filepath as src,       
            (fn.created*".$weights['brand partner released new flip'].") as s,
            ".cmwn_feed_get_timeago('fn.created')."
      	
            FROM {node} fn 
            JOIN {content_field_brand_partner} cfbp ON cfbp.nid = fn.nid AND cfbp.vid = fn.vid 
            JOIN {node} bpn on bpn.nid = cfbp.field_brand_partner_nid
            JOIN {content_field_icon} cfi on bpn.nid =  cfi.nid and bpn.vid = cfi.vid
            JOIN {files} f on f.fid = cfi.field_icon_fid
            WHERE fn.type='flip')";

    $feed_queries['new brand partner'] =  "(SELECT 
      	    CONCAT('<strong>Change My World Now</strong> is celebrating <a href=\"/node/', bpn.nid,'\">', bpn.title,'</a> as a new brand partner.') as excerpt, 
      	    f.filepath as src,       
            (bpn.created*".$weights['new brand partner'].") as s,
            ".cmwn_feed_get_timeago('bpn.created')."
            
            FROM {node} bpn
            JOIN {content_field_icon} cfi on bpn.nid =  cfi.nid and bpn.vid = cfi.vid
            JOIN {files} f on f.fid = cfi.field_icon_fid
            WHERE bpn.type = 'brand_partner')";
            
    $feed_queries['new brand partner'] =  "(SELECT 
      	    CONCAT('<strong>Change My World Now</strong> is celebrating <a href=\"/node/', bpn.nid,'\">', bpn.title,'</a> as a new brand partner.') as excerpt, 
      	    f.filepath as src,       
            (bpn.created*".$weights['new brand partner'].") as s,
            ".cmwn_feed_get_timeago('bpn.created')."
            
            FROM {node} bpn
            JOIN {content_field_icon} cfi on bpn.nid =  cfi.nid and bpn.vid = cfi.vid
            JOIN {files} f on f.fid = cfi.field_icon_fid
            WHERE bpn.type = 'brand_partner')";        
      
      $feed_queries['special edition flip'] =  "(SELECT 
      	    CONCAT('<a href=\"/node/', bpn.nid,'\">', bpn.title,'</a> has released a new flip action item called <em><a href=\"/node/', fn.nid,'\">' , fn.title , '</a></em>' ) as excerpt, 
      	    f.filepath as src,       
            (fn.created*".$weights['special edition flip'].") as s,
            ".cmwn_feed_get_timeago('fn.created')."
      	
            FROM {node} fn 
            JOIN {content_field_brand_partner} cfbp ON cfbp.nid = fn.nid AND cfbp.vid = fn.vid 
            JOIN {node} bpn on bpn.nid = cfbp.field_brand_partner_nid
            JOIN {content_field_icon} cfi on bpn.nid =  cfi.nid and bpn.vid = cfi.vid
            JOIN {files} f on f.fid = cfi.field_icon_fid
            WHERE fn.type='flip')";        
      
            
    
		$args = array();
    foreach($feed_queries as $type => $query){
      $args = array_merge($args,$friends);
    }

    $query_union = implode(' UNION ALL ', $feed_queries) . '  order by s desc';
    //print preg_replace('/[{}]/', '',$query_union);exit;
    $count_query = "SELECT COUNT(*) FROM (" . $query_union . ") AS count_query";
    
    $feed_items = pager_query($query_union, 13, 0, $count_query, $args);//careful here, $args must work for count query and main query or this wont work.
    
    while($f = db_fetch_object($feed_items)){
      $item = new stdClass();
  		$item->excerpt = $f->excerpt;
      $item->src = ($f->src);
  		//$item->stamp = $f->stamp;
  		$item->time_ago = $f->time_ago;
  		$items[] = $item;

    }
		?>
		
    <?php foreach ($items as $item) { ?>
      	<div class="item">
      		<span class="image">
      			<img height="42" src="/<?php print $item->src; ?>" width="42" />
      		</span>
      		<?php
      			$_excerpt = $item->excerpt  . ' <em class="feed-time">' .  $item->time_ago . '</em>';
      			$_excerpt = str_replace('/user/'.$user->uid, '/user', $_excerpt);
      			$_excerpt = preg_replace('/("\/user\/)([0-9]+)(")/i', '"/user/'.$user->uid.'/friends/$2/"', $_excerpt);
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