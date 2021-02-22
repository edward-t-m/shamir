# shamir39

Split mnemonic seeds into n-of-m BIP39 mnemonic shares using Shamir's Secret Sharing Scheme.


## Intent

To increase the likelihood of successfully passing on your crypto estate after your death.


## Motivation

Mnemonics seeds are a simple way to back up an entire crypto wallet. Crypto wallet backups should be hand-written, not digital,
and using mnemonics from a fixed wordlist significantly reduces the human risk of transcription errors compared to hex or other
representations of a wallet seed.

The downside of distributing these backups to a trusted party (to recover one's crypto after death) is that the funds
can easily be stolen before death (whether by the trusted party or compromsied from security failings on their part).

This results in 1) less sharing, and 2) more home-grown encryption or obfuscation schemes. Both of these reduce the chance of 
successful recovery by those responsible for managing the deceased's estate.

To address this, shamir39 splits mnemonic backup seeds into shares using [Shamir's Secret Sharing Scheme](https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing) (SSSS), 
expressing the shares themselves as BIP39 mnemonics. [BIP39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki#Abstract) is the name of the most common mnemonic format, hence naming the tool shamir39.

This removes the risk of a single compromised party losing all funds, but also retains the benefit of human readability, 
making it more likely that all backups can be fully recovered.


## Security Reviews

This code has not yet been reviewed for safety or security - not recommended to use yet for high value wallet backups.

## Specification

Shamir39 specification is [here](https://github.com/edward-t-m/shamir39-spec/blob/master/specification.md). 

## History

The code is a fork of MrJoy's [SSSS](https://github.com/MrJoy/ssss) "Shamir's Secret Sharing Scheme" (itself a fork of B. Poettering's [SSSS](http://point-at-infinity.org/ssss/index.html)), 
with the addition of ryepdx's [keyphrase](https://github.com/ryepdx/keyphrase) for mnemonic support, modified to support BIP39 wordlists.

The shamir39 specification was originally drafted by [Ian Coleman](https://github.com/iancoleman/shamir39/blob/master/specification.md).

## Version

SSSS fork is based on  `0.5.6` (SHA256: xxx).
Which is in turn based on `ssss-0.5.tar.gz` (SHA1: 3f8f5046c2c5c3a2cf1a93f0a9446681852b190e).


## License

Majority of this code follows the same license as that ssss project: The GPLv2.

Items from keyphrase project follows the same license as keyprhase: Affero GPL 

Some elements are unlicenced, others under the BSD-MIT License as noted in individual
files.

Edits comply with the corresponding licences above; original work is licensed under Affero GPL

