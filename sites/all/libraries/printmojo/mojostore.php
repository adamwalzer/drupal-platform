<?php

  /************************************************************************
   * PRINTMOJO.COM SYNDICATION SCRIPT
   *
   * This PHP script allows for the syndication of a printmojo store into
   * your own website, provided your website meets the basic requirements
   * of running PHP scripts.
   *
   * You will need PHP 4+
   *
   ************************************************************************/

   //--------------------------------------------------------------------//
   // CONFIGURATION
   // *************
   //

   //
   // We need to know who you are, you must enter your storename, username
   //  and password EXACTLY as they are at printmojo (case sensitive).
   //
   $_SERVER['store_name'] = 'ChangeMyWorldNow';      // The name of your store
   $_SERVER['username']   = 'marjoriej';            // Your printmojo username
   $_SERVER['password']   = 'stormycloud44';            //   and password

   //
   // The next item must be the full absolute URL to where this script is
   //  accessible on YOUR server.
   //
   $_SERVER['url']        = ($_SERVER['HTTPS'] ? 'https' : 'http').'://'.$_SERVER['HTTP_HOST'].'/store/';	// URL of mojostore.php on your server
   
   // To speed up requests the script can perform some caching, by default
   // "SESSION" caching is used, to speed up further on high traffic sites
   // you may use "FILE" caching, you will need to ensure that the directory
   // "mojocache" is writable by the webserver (777 permissions is safe)
   // Change the word SESSION to FILE if you want to use file caching
   $_SERVER['cache']      = 'SESSION';   
   
   // And thats it!  You only need to edit items below if you wish to change
   //  the way the pages are displayed to the web user.  If you dn't want to
   //  edit these just go to http://your.site.here/mojostore.php to see
   //  how things look!

   //---------------------------------------------------------------------//
   // TEMPLATES
   // *********
   //  As well as the main file 'pm_layout.html' which contains the
   //  wrapper that is displayed around the products, order form etc, you
   //  may also change the way the products, order form etc actually
   //  display within that wrapper.  These are called templates.
   //
   //  Each template consists of completely valid HTML code, interspersed
   //  with some special comments which mark out sections and subsections
   //  and special codes which include certain items in the place of the
   //  code.
   //
   //  There are a couple of codes that are available in all templates...
   //   {categories_link}   - this provides the url to view the categories
   //   {basket_link}       - this provides the url to view the basket

   // PRODUCT LISTING
   // ---------------
   //  This template contains the html necessary to display a *list* of
   //  products, both products within a category and all products.
   //
   // This template contains a subsection called 'EACH PRODUCT', this subsection
   //  is displayed for each product in the listing, within this subsection
   //  the following codes are available
   //
   //  {view_link}      - The URL to view & purchase the product
   //  {product_name}   - The name of the product
   //  {product_price}  - The price of the product
   //  {product_image_url}   - The URL to the image of the product
   //  {product_thumb_url}   - The URL to the thumbnail of the product
   //  {product_description} - The description of the product

   ob_start();
   ?>
    <!-- BEGIN PRODUCT LISTING -->
      <a class="basket" href="{basket_link}">View My Cart</a>
      <div class="products">
        <!-- BEGIN EACH PRODUCT -->
        <div class="product">
          <div class="image"><a href="{view_link}"><img src="{product_thumb_url}" alt="{product_name}" /></a></div>
          <a class="title" href="{view_link}">{product_name}</a>
          <div class="price">{product_price}</div>
          <!-- <div class="description">{product_description}</div> -->
          <!-- <a class="add-to-cart" href="{view_link}">Add to Cart</a> -->
        </div>
        <!-- END EACH PRODUCT -->
      </div>
    <!-- END PRODUCT LISTING -->
   <?php
   $_SERVER['product_list'] = ob_get_clean();


   // PRODUCT DETAILS
   // ---------------
   //  This template provides the html necessary to display a product and
   //   select the size & color for adding to the customers basket.
   //
   // The following codes are available in this template
   //  {product_name}
   //  {product_image_url}
   //  {product_description}
   //  {product_price}
   //  {mojo_add_item}  - The form action URL for the add item form
   //  {hidden_fields}  - The hidden fields required by the form
   //  {sizes}          - A selector to choose the size of the desired product
   //  {colors}         - A selector to choose the color of the desired product
   //
   // Also available is a special sub section called 'NO INVENTORY' which is
   //  shown when a user attempts to purchase the product but there is
   //  presently no inventory for the selected size/color combination.
   //
   ob_start();
   ?>
<a class="basket" href="{basket_link}">View My Cart</a>
    <!-- BEGIN PRODUCT DETAIL -->
    <div class="product-detail">
      <div class="image"><img src="{product_image_url}" alt="{product_name}" /></div>
      <div class="right">
        <h2 class="title">{product_name}</h2>
        <!-- BEGIN NO INVENTORY -->
        <div class="error">
         <strong> Sorry, there is not currently sufficient inventory in this product to satisfy your order. </strong>
        </div>
        <!-- END NO INVENTORY -->
        <div class="price">Price: {product_price}</div>
        <div class="description">
          {product_description}
        </div>
        <form action="{mojo_add_item}">
          {hidden_fields}
  
          {sizes}
  
          {colors}
  
          <input type="submit" value="Add To Cart" />
          <a href="" class="button blue"><span>add to my cart</span></a>
        </form>
      </div>
    </div>
    <!-- END PRODUCT DETAIL -->
    <script type="text/javascript">
    jQuery(function($){
      $('.product-detail .button').click(function(e){
        e.preventDefault();
        var $this = $(this);
        $this.prev()[0].click();
      });
    });
    </script>
   <?php
   $_SERVER['product_view'] = ob_get_clean();

   // VIEW BASKET
   // -----------
   // This template provides the html to display the customers current
   //  basket contents.  This template contains a number of subsections.
   //
   // Subsections
   // ...........
   //  "EACH ITEM"    - This section is displayed for each item in the basket
   //       codes available in this section are as follows
   //       {even_odd}    - either the word 'even' or 'odd' depending on wether
   //           it's an even or odd row (i.e it alternates between even and odd)
   //       {product_name}
   //       {color}       - the selected color
   //       {size}        - the selected size
   //       {quantity}    - the quantity being ordered
   //       {product_price} - the price for one of the product
   //       {line_total}    - the price for the quantity of the product
   // "BASKET EMPTY"   - This section is displayed only when the basket is empty
   // "TOTAL ITEMS"    - This section is displayed when the basket is not empty
   //       codes available in this section are as follows
   //       {total_items}   - the total number of items being ordered
   //       {sub_total}     - the price ex tax & shipping for this order
   // "SHIPPING"       - This section is displayed when a shipping price is applicable
   //       codes available in this section are as follows
   //       {shipping}      - the price for shipping the order
   // "TAX"            - This section is displayed when tax is applicable
   //       codes available in this section are as follows
   //       {tax}           - the price for tax on the order
   // "CHECKOUT"        - This section is displayed when there are products in the order
   //       codes available in this section are
   //       {checkout_link} - the link to checkout.
   //
   ob_start();
   ?>
    <!-- BEGIN VIEW BASKET -->
    <div class="cart">
      <a class="categories arrow-link" href="{all_products_link}">Continue Shopping</a>
    <div class="order">
      <table border=0 cellpadding=3 cellspacing=1 width=100%>
        <thead class="row1">
          <td class="first">Remove</td>
          <td ALIGN="left" width="60%"><b>Description</b></td>
          <td ALIGN="CENTER"><b>Color</b></td>
          <td ALIGN="CENTER"><b>Size</b></td>
          <td ALIGN="center"><b>Qty</b></td>
          <td ALIGN="CENTER"><b>Price Each</b></td>
          <td ALIGN="CENTER" class="last"><b>Sub Total</b></td>
        </thead>

        <form action="{mojo_update_totals}" method="POST">
        <!-- BEGIN EACH ITEM -->
        <tr class="{even_odd}">
          <td class="first"><a class="remove" href="{mojo_remove_item}">Remove</a></td>
          <td>{product_name}</td>
          <td align=center>{color}</td>
          <td align=center>{size}</td>
          <td align=center>
            <input type="hidden" name="BProd[{group_key}][CustomProductID]" value="{custom_product_id}" />
            <input type="hidden" name="BProd[{group_key}][ColorID]" value="{color_id}" />
            <input type="hidden" name="BProd[{group_key}][SizeID]" value="{size_id}"   />
            <input type="text"   name="BProd[{group_key}][Quantity]" value="{quantity}" size="3" />
          </td>
          <td align=right>{product_price}</td>
          <td align=right class="last">{line_total}</td>
        </tr>
        <!-- END EACH ITEM -->
        <tr class="update">
          <td align="right" colspan="7">
            <font class="error">{e_insufficient_inventory}</font>
            <input type="submit" value="Update Totals" />
            <a href="#" class="arrow-link">Update Totals</a>
    <script type="text/javascript">
    jQuery(function($){
      $('.update .arrow-link').click(function(e){
        e.preventDefault();
        var $this = $(this);
        $this.prev()[0].click();
      });
    });
    </script>
          </td>
        </tr>
        </form>

        <!-- BEGIN BASKET EMPTY -->
        <tr class="odd">
          <td colspan=7 align=center class="first last"><br><p>Your Shopping Cart is currently empty.</p><br></td>
        </tr>
        <!-- END BASKET EMPTY -->

        <!-- BEGIN TOTAL ITEMS -->
        <tr>
          <td align="right" colspan="6" class="first"><font class="body"><b>Total Items:</b></font></td>
          <td align="right"><strong>{total_items}</strong></td>
        </tr>
        <tr>
          <td align="right" colspan=6><font class="body"><b>Subtotal:</b></font></td>
          <td align=right class="last"><font class="body"><b>{sub_total}</b></td>
        </tr>
        <!-- END TOTAL ITEMS -->

        <!-- BEGIN VOUCHER -->
        <tr class="even coupon">
          <td align="right" colspan="6" class="first">
            <font class="error">{e_voucher_invalid}</font>
            <form action="{voucher_url}" method="POST">
              <div class="coupon_wrapper">
                <label for="coupon_code"><b>Coupon :</b></label>
                <input id="coupon_code" type="text" name="Voucher" value="{voucher_code}" size="10" />
              </div>
              <input type="submit" class="submit" value="Apply" />
              <a href="#" class="arrow-link">Apply Coupon</a> 
              <script type="text/javascript">
              jQuery(function($){
                $('.coupon .arrow-link').click(function(e){
                  e.preventDefault();
                  var $this = $(this);
                  $this.prev()[0].click();
                });
              });
              </script>
            </form>
          </td>
          <td align=right class="last"><font class="body"><b>{voucher_discount}</b></td>
        </tr>
        <!-- END VOUCHER -->

        <!-- BEGIN SHIPPING -->
        <tr class="even">
          <td align="right" colspan=6 class="first"><font class="body"><b>Shipping:</b></font></td>
          <td align=right class="last"><b>{shipping}</b></td>
        </tr>
        <!-- END SHIPPING -->

        <!-- BEGIN TAX -->
        <tr class="even">
          <td align="right" colspan=6 class="first"><font class="body"><b>Tax:</b></font></td>
          <td align=right class="last"><b>{tax}</b></td>
        </tr>
        <!-- END TAX -->

        <!-- BEGIN TOTAL -->
        <tr class="even">
          <td align="right" colspan=6 class="first"><font class="body"><b>Order Total:</b></font></td>
          <td align=right class="last"><b>{grand_total}</b></td>
        </tr>
        <!-- END TOTAL -->

      </table>


    </div>

    <table class="buttons" width="100%" cellspacing="0" cellpadding="0">
      <tr>
        <td width="30%" align="left"></td>
        <!-- BEGIN CHECKOUT -->
        <td width="30%" align="right"><a style="float:right;margin:24px 0 8px 0;" class="checkout button blue" href="{checkout_link}"><span>purchase these products</span></a></td>
        <!-- END CHECKOUT -->
      </tr>
    </table>
</div>
    <!-- END VIEW BASKET -->
   <?php
   $_SERVER['view_basket'] = ob_get_clean();

   // LIST CATEGORIES
   // ---------------
   //  This template contains the html necessary to display a list of
   //  categories.  It contains a subsection named 'EACH CATEGORY' which
   //  is displayed for each category.
   //
   //  Within the 'EACH CATEGORY' subsection the following codes are available
   //   {category_products_link}    - The link to display the products in this
   //                                   category
   //   {category_name}             - The name of this category.
   //
   ob_start();
   ?>
   <!-- BEGIN LIST CATEGORIES -->
   <div class="list categories">
     <label>Product Categories</label>
     <div class="list">
      <!-- BEGIN EACH CATEGORY -->
      <a class="category" href="{category_products_link}">{category_name}</a>
      <!-- END EACH CATEGORY -->
      <div class="breaker">&nbsp;</div>
     </div>
   </div>
   <!-- END LIST CATEGORIES -->

   <table class="buttons" width="100%" cellspacing="0" cellpadding="0">
      <tr>
        <td align="center"><a class="basket" href="{basket_link}">View Your Shopping Basket</a></td>
      </tr>
    </table>
   <?php
   $_SERVER['list_categories'] = ob_get_clean();

   //--------------------------------------------------------------------//
   // Thats all the configuration, you should now be able to
   //  http://www.yoursite.com/mojostore.php
   ////////////////////////////////////////////////////////////////////////





















                  // This space intentionally left blank //























   ////////////////////////////////////////////////////////////////////////
   //  NO EDITING BEYOND THIS POINT
   ///////////////////////////////////////////////////////////////////////

   $_SERVER['mojo_url']   = 'https://www.printmojo.com/';
   $_SERVER['store_data'] = get_store_data();
   $_SERVER['layout']     = dirname(__FILE__) . '/pm_layout.html';


   function basket(&$data)
   {
     $Ref = $_GET['ref'];
     $fh = @fopen($_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_Basket.php?ref=' . rawurlencode($_GET['ref']), 'r');
     if(!$fh)
     {
       header("location: " . $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_Basket.php');
       exit;
     }

     $data = '';
     $d    = FALSE;
     while($d = fread($fh, 1024))
     {
       $data .= $d;
     }
     fclose($fh);
     $data = trim($data);
     $data = unserialize($data);
     if(!$data)
     {
       header("location: " . $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_Basket.php');
       exit;
     }

     $t_basket = $_SERVER['view_basket'];
     $t = array();
     foreach(array('EACH ITEM', 'BASKET EMPTY', 'TOTAL ITEMS', 'VOUCHER', 'SHIPPING', 'TAX', 'TOTAL', 'CHECKOUT') as $subsection)
     {
       $t[$subsection] =
        preg_replace("/.*<!-- BEGIN {$subsection} -->(.*)<!-- END {$subsection} -->.*/is", '$1', $t_basket);
       $t_basket =
        preg_replace("/<!-- BEGIN {$subsection} -->.*<!-- END {$subsection} -->/is", '{' . $subsection . '}', $t_basket);
     }
     $basket_load =
      array
        (
         '{EACH ITEM}'    => '',
         '{BASKET EMPTY}' => '',
         '{TOTAL ITEMS}'  => '',
         '{SHIPPING}'     => '',
         '{TAX}'          => '',
         '{TOTAL}'        => '',
         '{CHECKOUT}'        => '',
         '{VOUCHER}'      => '',
         '{mojo_update_totals}' => $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_Basket.php?Syndicator=' . rawurlencode($_SERVER['url']) . '&Reflect=1&ref=' . $_GET['ref'],
         '{e_insufficient_inventory}' => @$_GET['Error'] === 'E_INSUFFICIENT' ? 'Insufficient Inventory Available': ''

         );

     $row = 0;
      if ($data['line_items'])
      {
        $row = 0;
        foreach($data['line_items'] as $ItemID => $ItemInfo)
        {
          $load = array
            ('even_odd' => ($row++ % 2 ? 'even' : 'odd'),
             'mojo_remove_item' =>  $_SERVER['mojo_url'] . $_SERVER['store_name'] . "/Store/Syndicated_RemoveItem.php?ItemID=" . urlencode(implode(',', $ItemInfo['ItemKeys'])) . "&Syndicator=" . rawurlencode($_SERVER['url']) . "&ref=" . $_GET['ref'],
             'product_name' => $ItemInfo['Product'],
             'color'        => $ItemInfo['Color'],
             'size'         => $ItemInfo['Size'],
             'quantity'     => $ItemInfo['Quantity'],
             'product_price'=> '$'. number_format($ItemInfo['Price'], 2),
             'line_total'   => '$'. number_format($ItemInfo['Total'], 2),
             'color_id'     => $ItemInfo['ColorID'],
             'size_id'      => $ItemInfo['SizeID'],
             'custom_product_id' => $ItemInfo['CustomProductID'],
             'group_key'         => $ItemInfo['GroupKey']
            );
            $load = array_quote_keys($load, '{', '}');
            $basket_load['{EACH ITEM}'] .= strtr($t['EACH ITEM'], $load);
        }

        $vch_load = array('{voucher_code}' => $data['voucher_code'],
                          '{voucher_discount}' => '$' . number_format($data['voucher_discount'],2),
                          '{voucher_url}' => $_SERVER['mojo_url'] . $_SERVER['store_name'] . "/Store/Syndicated_EnterVoucher.php?Syndicator=" . rawurlencode($_SERVER['url']),
                          '{e_voucher_invalid}' => @$_GET['Error'] === 'E_VOUCHER_INVALID' ? 'Invalid/Expired': ''
                          );
        $basket_load['{VOUCHER}'] = strtr($t['VOUCHER'], $vch_load);

        $ti_load = array('{total_items}' => $data['total_items'],'{sub_total}' => '$' . number_format($data['sub_total'], 2));
        $basket_load['{TOTAL ITEMS}'] = strtr($t['TOTAL ITEMS'], $ti_load);

        $sh_load = array('{shipping}' => '$' . number_format($data['shipping_total'], 2));
        $basket_load['{SHIPPING}'] = strtr($t['SHIPPING'], $sh_load);

        if(is_numeric($data['tax_total']))
        {
          $tx_load = array('{tax_total}' => '$' . number_format($data['tax_total'], 2));
          $basket_load['{TAX}'] = strtr($t['TAX'], $tx_load);
        }

        $to_load = array('{grand_total}' => '$' . number_format($data['total'], 2));
        $basket_load['{TOTAL}'] = strtr($t['TOTAL'], $to_load);

        $bu_load = array('{checkout_link}' => $_SERVER['mojo_url'] . $_SERVER['store_name'] . "/Store/Address.php?Syndicator=" . rawurlencode($_SERVER['url']));
        $basket_load['{CHECKOUT}'] = strtr($t['CHECKOUT'], $bu_load);
      }
      else
      {
        $basket_load['{BASKET EMPTY}'] = $t['BASKET EMPTY'];
      }

      return strtr($t_basket, $basket_load);
   }

   function view_product(&$data, &$title_holder)
   {
     $ProductID = $_GET['ProductID'];
     if(!isset($data['products'][$ProductID]))
     {
       trigger_error('Invalid Product Identifier', E_USER_ERROR);
     }

     $t_product = preg_replace('/<!-- BEGIN NO INVENTORY -->.*<!-- END NO INVENTORY -->/is', '{NO INVENTORY}', $_SERVER['product_view']);
     $t_noinv = preg_replace('/.*<!-- BEGIN NO INVENTORY -->(.*)<!-- END NO INVENTORY -->.*/is', '$1', $_SERVER['product_view']);

     $product = $data['products'][$ProductID];
     $title_holder = htmlspecialchars($product['ProductName']);
     $load = array
       (
        'view_link'   =>  htmlspecialchars($_SERVER['PHP_SELF'] . "?_=view&ProductID={$product['CustomProductID']}"),
        'product_name' => htmlspecialchars($product['ProductName']),
        'product_price' => '$' . number_format($product['MarkupAmount'], 2),
        'product_image_url' => htmlspecialchars($product['mainimagelink']),
        'product_thumb_url' => htmlspecialchars($product['thumbimagelink']),
        'product_description' => $product['Description'],
        'mojo_add_item'       => $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_AddItem.php',
        'hidden_fields'       => "<input type=\"hidden\" name=\"ProductID\"  value=\"{$ProductID}\" />
                                  <input type=\"hidden\" name=\"Syndicator\" value=\"" . htmlspecialchars($_SERVER['url']) . "\" />",
       );

     if(isset($_GET['InvOut']))
     {
       $load['NO INVENTORY'] = $t_noinv;
     }
     else
     {
       $load['NO INVENTORY'] = '';
     }

     ob_start();
      if($product['sizes'])
      {
        ?>
        <div class="select-wrap">
        <label for="SizeID">Size:</label>
        <select id="SizeID" name="SizeID">
          <?php
            foreach($product['sizes'] as $size)
            {
              ?>
              <option value="<?php echo $size['SizeID'] ?>"><?php echo htmlspecialchars($size['SizeName']) ?></option>
              <?php
            }
          ?>
        </select>
        </div>
        <?php
      }
     $load['sizes'] = ob_get_clean();

     ob_start();
      if($product['colours'])
      {
        ?>
        <div class="select-wrap">
        <label for="ColorID">Color:</label>
        <select name="ColorID">
          <?php
            foreach($product['colours'] as $colour)
            {
              ?>
              <option value="<?php echo $colour['FabricColorID'] ?>"><?php echo htmlspecialchars($colour['ColorName']) ?></option>
              <?php
            }
          ?>
        </select>
        </div>
        <?php
      }
     $load['colors'] = ob_get_clean();


     foreach($load as $k => $v)
     {
       $t_product = str_replace('{' . $k . '}', $v, $t_product);
     }

     return $t_product;
   }

   function list_categories(&$data)
   {
     $t_categories = $_SERVER['list_categories'];
     $t_categories = preg_replace('/<!-- BEGIN EACH CATEGORY -->(.*)<!-- END EACH CATEGORY -->/s', '{categories}', $_SERVER['list_categories']);

     $t_line = preg_replace('/.*<!-- BEGIN EACH CATEGORY -->(.*)<!-- END EACH CATEGORY -->.*/s', '<!-- BEGIN CATEGORY -->$1<!-- END CATEGORY -->', $_SERVER['list_categories']);
     $c_load = array('{categories}' => '');

     foreach($data['categories'] as $category)
     {
       $c_load['{categories}'] .= strtr($t_line, array('{category_products_link}' => $_SERVER['url'] . '?_=list&Category=' . $category['CategoryID'], '{category_name}' => $category['CategoryName']));
     }
     return strtr($t_categories, $c_load);
   }

   function list_products(&$data)
   {
     $Cat = @$_GET['Category'];

     $t_list = preg_replace('/<!-- BEGIN EACH PRODUCT -->(.*)<!-- END EACH PRODUCT -->/s', '{products}', $_SERVER['product_list']);
     $t_line = preg_replace('/.*<!-- BEGIN EACH PRODUCT -->(.*)<!-- END EACH PRODUCT -->.*/s', '<!-- BEGIN PRODUCT -->$1<!-- END PRODUCT -->', $_SERVER['product_list']);

     ob_start();
     foreach($data['products'] as $product)
     {
       if($Cat && !in_array($product['CustomProductID'], $data['categories'][$Cat]['product_ids']))
       {
         continue;
       }

       $load =
         array
           (
            'view_link'   =>  htmlspecialchars("?_=view&ProductID={$product['CustomProductID']}"),
            'product_name' => htmlspecialchars($product['ProductName']),
            'product_price' => '$' . number_format($product['MarkupAmount'], 2),
            'product_image_url' => htmlspecialchars($product['mainimagelink']),
            'product_thumb_url' => htmlspecialchars($product['thumbimagelink']),
            'product_description' => $product['Description']
           );

       $item = $t_line;
       foreach($load as $k => $v)
       {
         $item = str_replace('{' . $k . '}', $v, $item);
       }
       echo $item;
       unset($item);
     }

     return str_replace('{products}', ob_get_clean(), $t_list);
   }

   function get_store_data($store = NULL, $user = NULL, $pass = NULL, $nocache = FALSE)
   {          
     $store = isset($store) ? $store : $_SERVER['store_name'];
     $user  = isset($user)  ? $user  : $_SERVER['username'];
     $pass  = isset($pass)  ? $pass  : $_SERVER['password'];

     if(!$nocache)
     {
       $cachekey = md5($store.$user.$pass);
       switch(@$_SERVER['cache'])
       {
          case 'SESSION':
            @session_start();
            if(isset($_SESSION[$cachekey]))
              return $_SESSION[$cachekey];
            return $_SESSSION[$cachekey] = get_store_data($store,$user,$pass,TRUE);
            
          case 'FILE':
            $cachefile = dirname(__FILE__) . '/mojocache/'.$cachekey.'.php';
            if(file_exists($cachefile))
              return include($cachefile);
            $data = get_store_data($store,$user,$pass,TRUE);
            ob_start();
            var_export($data);
            $cache = '<'.'?php return ' . ob_get_clean() . '; ?'.'>';
            $fh = fopen($cachefile, 'w');
            if(!$fh) 
            {
              trigger_error("Cache directory could not be written to.", E_USER_WARNING);
            }
            else
            {
              fwrite($fh, $cache, strlen($cache));
              fclose($fh);
            }
            return $data;
       }
     }
     
     $fh = @fopen($_SERVER['mojo_url'] . $store . '/Store/Syndicated_DataFeed.php'
                  . '?Store=' . rawurlencode($store)
                  . '&User='  . rawurlencode($user)
                  . '&Pass='  . rawurlencode($pass), 'r');
     if(!$fh)
     {
       trigger_error('Unable to access your store data, check the username and password.', E_USER_ERROR);
     }

     $data = '';
     $d    = FALSE;
     while($d = fread($fh, 1024))
     {
       $data .= $d;
     }
     fclose($fh);
     $data = trim($data);

     if(!preg_match('/^Status: ([0-9]+)(\s[^\n]*)?\n(.*)/s', $data, $m))
     {
       print_r($data);
       trigger_error('A malformed response was retrieved from PrintMojo.  Please contact PrintMojo.', E_USER_ERROR);
     }

     $status = array($m[1], $m[2]);
     $data   = $m[3];
     if(!handle_status($status[0], $status[1])) exit;

     $data   = trim($data);

     $data   = unserialize($data);
     if(!$data) trigger_error('A malformed response was retrieved from PrintMojo.  Please contact PrintMojo', E_USER_ERROR);

     return $data;
   }

   function handle_status($code, $message = NULL)
   {
     $code = (int) $code;
     if($code < 300)
     {
       return TRUE;
     }

     if($code >= 400)
     {
      trigger_error($message, E_USER_ERROR);
      return FALSE;
     }

     return FALSE;
   }

   function wrap_html($html, $title_text = 'Online Shopping')
   {
     //$html .= "<a href=\"http://www.printmojo.com/\" class=\"branding\">Powered by PrintMojo</div>";
     $html = strtr($html,
                    array
                      (
                       '{basket_link}' => $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_Basket.php?Syndicator=' . rawurlencode($_SERVER['url']) . '&Reflect=1',
                       '{categories_link}'   => $_SERVER['url'] . '?_=list_categories',
                       '{all_products_link}' => $_SERVER['url'] . '?_=list',
                       '{checkout_link}' => $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Address.php?Syndicator=' . rawurlencode($_SERVER['url']) . '&Reflect=1',
                       '{title_text}' => $title_text

                       )
                   );

     //$t_layout = implode('', file($_SERVER['layout']));
     //$out = strtr($t_layout, array('{body}' => $html, '{basket_link}' => $_SERVER['mojo_url'] . $_SERVER['store_name'] . '/Store/Syndicated_Basket.php?Syndicator=' . rawurlencode($_SERVER['url']) . '&Reflect=1', '{title_text}' => $title_text));
     //$out = preg_replace('/<\/title>/', ' - Powered by PrintMojo</title>', $out);
     return $html;
   }

   if(!function_exists('ob_get_clean'))
   {
     function ob_get_clean()
     {
       $x = ob_get_contents();
       ob_end_clean();
       return $x;
     }
   }

   function array_quote_keys($array, $o = "'", $c = "'")
   {
     $n = array();
     foreach($array as $k => $v)
     {
       $n[$o . $k . $c] = $v;
     }
     return $n;
   }
?>