<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', 'wordpress' );

/** MySQL database password */
define( 'DB_PASSWORD', 'wppassword' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8mb4' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         't&ElUQy9,l;Di1JR{$LW2mVQ8g~j{VHfk[<Fr]P{`fYg;Du}0ugi1n(>PX9A$$q,' );
define( 'SECURE_AUTH_KEY',  '4PF~Tr@`uiIF8*UGa!/z2=20i~Ky52_%n=x#/w%F}w9e`N-UEZHa?rDJ+0D^E:1M' );
define( 'LOGGED_IN_KEY',    '4hw;x{/`OG{tqUx[o=x!E*Z}`XVd&85HM/AQw+S#@U+KCc91!# -QKiKRhnl(_ 3' );
define( 'NONCE_KEY',        ' .+VLn(t%7rpr!&/RC<Lvjo)V8r`i1q=A={/je)SciZ={KppKBrRkV.v*RB}||~$' );
define( 'AUTH_SALT',        'P//Vba%+>bak)dkFc{M%W:.Y}:kZ$d@|5Xt}z&RNf-M_sr8i%xlYkb1#O6Bb*GZ?' );
define( 'SECURE_AUTH_SALT', 'O R~iq-;>M@+K#M,AKj<!Q[O:Uu@$7s87Pd`zJDL},XeqwlV~c_lCJ:pjNKmy#Ll' );
define( 'LOGGED_IN_SALT',   '02Fz@:xxdp|`Dvx_3}`rWlYIxE`59TU9`@OZ6aE2xhL>ZSi)7m~{ sh|WQv@M9)<' );
define( 'NONCE_SALT',       'O%+(@o#(~HvP.d%LY&{z{bNTp4iFf{)=MfJt@]zuf{eRCAyWtM(H6i`cgk8SmFvb' );

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', dirname( __FILE__ ) . '/' );
}

/** Sets up WordPress vars and included files. */
require_once( ABSPATH . 'wp-settings.php' );