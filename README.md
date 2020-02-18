# shamir39

BIP39 mnemonic seeds split/shared/combined using Shamir's Secret Sharing Scheme


## History

This is a fork of B. Poettering's SSSS ("Shamir's Secret Sharing Scheme").


## Intent

This fork of ssss exists is intended to implement [Ian Coleman's shamir39 specification](https://github.com/iancoleman/shamir39/blob/master/specification.md),
to facilitate its use in real-world usage scenarios, specifically BIP39 mnemonic seeds used in Bitcoin and other cryptocurrencies.




## What You Need To Know

Please read B. Poettering's page on SSSS before proceeding.  SSSS, like all
cryptographic algorithms, can lead to a false sense of security if improperly
used.  Be sure you understand the role it serves, and the limitations it has
before employing it.

[http://point-at-infinity.org/ssss/index.html](http://point-at-infinity.org/ssfdasadfsass/index.html)


## Version

This fork is based on  `0.5.6` (SHA256: xxx).
Which is in turn based on `ssss-0.5.tar.gz` (SHA1: 3f8f5046c2c5c3a2cf1a93f0a9446681852b190e).


## Verification and Installation (VERY IMPORTANT!)
//TODO commit with my gpg keys, add signed SHASUM file and update this bit

Before installing, when cloning this repo, use a signed tag and verify the
gpg signature first!

```bash
# First, you need to make sure you have the signing key in your GPG keychain:
gpg --keyserver sks-keyservers.net --recv-key 7DCB12A7

# Now, clone the repo, and verify it:
git clone http://github.com/MrJoy/ssss.git
git tag -v v0.5.6
# You should see output to the effect of:
#   gpg: Signature made <date and time> using RSA key ID 7DCB12A7
#   gpg: Good signature from "Jon Frisby <jfrisby@mrjoy.com>"
#
# If you do NOT see 'Good Signature from "Jon Frisby <jfrisby@mrjoy.com>" and
# the RSA key ID 7DCB12A7 then do not proceed with installation!
#
git checkout v0.5.6 # This will put you in 'detached head' mode, which is fine
                    # but don't make changes as you are no longer on a branch!
# Proceed with build steps from here.  See `INSTALL.md` for details.
```

Jon Frisby's GPG key signature is at [MrJoy.com](http://MrJoy.com).


## License

This fork of ssss follows the same license as that ssss project: The GPLv2.
Items from keyphrase project follows the same license as keyprhase: Affero GPL

