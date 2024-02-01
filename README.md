# DUNE_LDO_lifetime
## Connect to BNL desktop remotely
> Download [Cisco AnyConnect](https://www.cisco.com/c/en/us/support/security/anyconnect-secure-mobility-client/series.html) and [Microsoft Remote Desktop](https://apps.apple.com/us/app/microsoft-remote-desktop/id1295203466?mt=12)
> [BNL instructions](https://www.bnl.gov/cybersecurity/vpn/)
1. Log in to Cisco AnyConnect: ```vpngateway.bnl.gov```
2. Approve log in via DUO app
3. Connect to BNL desktop using Microsoft Remote Desktop
## Introductions to LP/ADM
1. [LP](https://www.ti.com/lit/ds/symlink/lp3964.pdf?ts=1688670238333&ref_url=https%253A%252F%252Fwww.google.com%252F)
2. [ADM](https://www.analog.com/media/en/technical-documentation/data-sheets/ADM7151.pdf)
## Run scripts
```python .\ldo_measure.py .\config.json```
> Remember to change the stress voltage in config.json, 2470->LP, 2460->ADM
