.. _rfc9:

====================================================================
PROJ RFC 9: Contributor agreement
====================================================================

:Author: Kristian Evers
:Contact: kristian@evers.dev
:Status: Proposed
:Initial version: 2026-11-11
:Last Updated: 2026-11-11

Summary
-------

This RFC proposes a formal contributor agreement that must be accepted before a
person can create a pull request against the PROJ and PROJ-data repositories.
The agreement covers the licensing of contributions, responsible use of AI
tools, and adherence to the project's code of conduct. It is accepted by
sending an introductory message to the PROJ mailing list. Once accepted, the
contributor is added to a GitHub team with write access to the repositories, and
pull request creation is restricted to collaborators. Existing PROJ committers
are exempt from the acceptance requirement.

The agreement is intended to make expectations explicit and to protect
maintainer time. It is not a ban on AI tools and it does not replace the
existing :ref:`ai_tool_policy` or :ref:`code_of_conduct`.

Motivation
----------

Maintainers report a growing number of first-time, low-context pull requests
that show little evidence of human review and appear to be produced with minimal
engagement with the project. Reviewing such contributions is expensive. When
the marginal cost of reviewing and merging a contribution is larger than the
marginal benefit to the project, the contribution is *extractive* rather than
*non-extractive* (see the :ref:`ai_tool_policy`). A steady stream of low-quality
pull requests leads to reviewer fatigue and is a net negative for the long term
sustainability of the project.

The problem is not limited to review effort. PROJ shares continuous integration
(CI) capacity and cost with GDAL and the other OSGeo projects in the
organisation, so excessive or unnecessary CI runs affect the wider community.
There is also uncertainty about the provenance of some contributions: the
project needs a named human who is accountable for a contribution and who
declares that they have the right to submit it under the project license.

At the same time, the community is weakened when the use of an LLM replaces
engagement with the people maintaining the project. The intent of this RFC is
therefore not to ban AI tools. It is to set clear expectations for
contributions, reduce the number of low-quality submissions, protect maintainer
time, and preserve human-to-human collaboration in the PROJ community.

Goals and non-goals
-------------------

Goals:

- Make the project's expectations clear before a contribution is reviewed.
- Ensure that every contribution has a named, accountable human and a clear
  licensing attestation.
- Reduce the number of low-quality or extractive contributions and the CI
  resources they consume.
- Preserve human-to-human collaboration and create a deliberate onboarding
  point for new contributors.
- Give maintainers a clear and consistent basis for declining contributions
  that do not meet the project's expectations.

Non-goals:

- Banning AI tools or policing which tools a contributor uses.
- Replacing the :ref:`ai_tool_policy` or the :ref:`code_of_conduct`.
- Restricting issues, discussions, security reports, or participation on the
  mailing list.
- Judging a contribution solely by whether AI tools were used.
- Creating a copyright assignment or a traditional contributor license
  agreement (CLA).

Terminology
-----------

Contributor
    Anyone who submits code, documentation, an RFC, an issue, a review comment,
    or another contribution to the project.

Committer
    A person with write access to the OSGeo/PROJ or OSGeo/PROJ-data
    repositories.

Maintainer
    A PSC member or committer who is responsible for reviewing and merging
    contributions.

Collaborator
    A GitHub user with the write, maintain, or admin role on a repository.

Signatory
    A contributor who has accepted the contributor agreement described in this
    RFC.

Agreement
    The terms in `The contributor agreement`_ below.

Background
----------

PROJ already has an :ref:`ai_tool_policy`, which requires a human in the loop,
mandates that contributors read and review all tool-generated content before
asking for review, and requires tool use to be labelled. The pull request and
issue templates contain a checkbox for that purpose. The policy applies to
code, RFCs, issues, and comments, but it does not require a contributor to
identify themselves or to declare that they have the right to submit their
contribution. The existing copyright and licensing guidance in
:file:`CONTRIBUTING.md` covers provenance in general terms, but it is not a
formal acceptance step.

An earlier attempt to adopt the GDAL contribution policy did not gain traction.
The discussion on the PROJ PSC email thread in November 2026 converged on a
formal contributor agreement instead. The proposal is inspired by the
contribution clauses used in the Rust community and by the CI hardening
proposed for PDAL.

The agreement supplements, and does not replace, the :ref:`ai_tool_policy`,
the :ref:`code_of_conduct`, and the existing copyright and licensing guidance.
Where the documents overlap, the more specific document applies: the
:ref:`ai_tool_policy` remains authoritative for how AI tools may be used, and
the :ref:`code_of_conduct` remains authoritative for conduct.

The contributor agreement
-------------------------

The normative text that contributors accept is given in `Agreement text`_.
The notes that follow explain each part and are not themselves part of the
text that contributors accept. When the RFC is adopted, the agreement text
should be copied verbatim into a single canonical location in the repository
and linked from the other contribution documents.

Agreement text
++++++++++++++

By accepting this agreement, a contributor agrees to the following.

1. **Licensing.** Unless you explicitly state otherwise in writing before
   submitting a contribution, any contribution intentionally submitted for
   inclusion in the work by you shall be licensed according to the MIT license,
   as described in the project's :file:`COPYING` file, without any additional
   terms or conditions. Any different terms must be agreed with the project in
   writing before the contribution is submitted.

2. **Responsible use of AI tools.** You are responsible for all contributions
   and communications that you submit. You will:

   - review all tool-generated content before submitting it, understand it, and
     be able to answer questions about it during review;
   - disclose substantial tool-generated content in the pull request
     description or commit messages, as required by the :ref:`ai_tool_policy`;
   - not use an AI agent as an intermediary in maintainer communication. Do not
     paste maintainer feedback into a model and submit its output without
     understanding it, editing it, and taking responsibility for it;
   - not submit contributions that you cannot explain or maintain;
   - keep changes focused, include appropriate tests and documentation, and
     respond to review feedback in a timely manner. Maintainers may close
     contributions that cannot be reviewed within a reasonable effort or that
     do not meet the project's contribution guidelines.

   Use of AI tools is permitted. Translation and copy-editing tools may be
   used for the acceptance message, provided that you review the result and
   remain accountable for it.

3. **Code of conduct.** You agree to respect the :ref:`code_of_conduct`.

A contributor accepts the agreement by sending a message to the
`PROJ mailing list`_ in which they:

- introduce themselves, including their background, their current affiliation
  if they wish to share it, and their motivation for contributing;
- state their GitHub username;
- declare that they accept the contributor agreement.

The message must be authored and submitted by the contributor. Autonomous
agents may not send it on the contributor's behalf. The message is public and
is archived by the mailing list; contributors should include only information
that they are comfortable sharing publicly.

.. _`PROJ mailing list`: http://lists.osgeo.org/mailman/listinfo/proj

Notes on the agreement
++++++++++++++++++++++

Licensing
~~~~~~~~~

The licensing wording is inspired by the contribution clause commonly used in
the Rust community, adapted for PROJ's MIT-only licensing. It is an
inbound=outbound declaration: contributions are accepted under the same
license as the project. It is not a copyright assignment and it does not grant
the project additional rights beyond the project license.

The clause allows a contributor to state different terms in writing before
submitting a contribution. In practice, the project is unlikely to accept
contributions under different terms, and any such request must be agreed in
writing in advance.

The wording should be reviewed by OSGeo legal counsel before adoption. If a
per-commit attestation is desired in addition to the one-time acceptance, a
Developer Certificate of Origin (DCO) sign-off could be added later; see
`Alternatives considered`_.

Responsible use of AI tools
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The AI terms restate and make explicit the expectations of the
:ref:`ai_tool_policy`. They do not introduce a new AI policy. The key
requirements are human review, disclosure, accountability, and direct
human-to-human communication with maintainers.

The prohibition on using an AI agent as an intermediary is about
accountability, not about the tools themselves. Contributors may use
translation, copy-editing, and similar assistive tools, provided that they
review the result and remain responsible for it.

The project does not require contributors to avoid AI tools for trivial
changes, but contributors should consider whether the review burden of a
change is justified by its benefit to the project. This is a norm, not a
separate enforceable rule.

Code of conduct
~~~~~~~~~~~~~~~

The code of conduct already applies to everyone who participates in the PROJ
community. The agreement makes acceptance of it an explicit part of becoming a
signatory.

Accepting the agreement
~~~~~~~~~~~~~~~~~~~~~~~

The introductory message serves several purposes: it confirms that the
contributor is a human who is accountable for their contributions, it gives the
community a chance to welcome the contributor, and it creates a durable record
of acceptance.

Because the message is public, affiliation is optional. Contributors who do not
wish to disclose their employer or other affiliation may omit it. The PSC may
revisit this requirement if it proves to be a barrier for legitimate
contributors.

Enforcement and administration
------------------------------

The agreement is enforced by restricting who can create pull requests. A GitHub
team, for example ``proj-contributors``, is given write access to the
OSGeo/PROJ and OSGeo/PROJ-data repositories, and the repositories are configured
to restrict pull requests to collaborators.

GitHub's "restrict pull requests to collaborators" setting, available since
February 2026, only allows users with write, maintain or admin access to create
pull requests. A contributor therefore needs write access to the repositories,
not merely read access. This also prevents non-collaborators from opening pull
requests from forks. Branch protection rules continue to govern who may merge
changes.

The PSC Chair is the primary administrator of the team. A named backup
administrator handles requests when the Chair is unavailable. Administrators:

- acknowledge receipt of introductory messages;
- verify that the message contains the required information;
- add the contributor to the team;
- keep a durable record of accepted contributors for audit purposes;
- remove contributors who violate the agreement or the code of conduct.

Administrators should aim to respond to an introductory message within five
business days. The operational record of signatories is the GitHub team
membership; the durable audit record should be kept in an access-controlled
location and should not contain more personal information than necessary.

A contributor who is removed from the team may appeal to the PSC. Violations
are handled according to the "Handling Violations" section of the
:ref:`ai_tool_policy` and the :ref:`code_of_conduct`.

Automated accounts, such as dependency and release bots, are added as
collaborators by the administrators and are exempt from the introductory
message. Security reports made through the project's private security channels
are exempt from this process.

Transition and backward compatibility
-------------------------------------

Contributors who are already PROJ committers at the time this RFC is adopted
are exempt from the acceptance requirement. A snapshot of the committer list is
recorded when the RFC is adopted, so that the exemption does not depend on
future changes to repository access. Existing committers are encouraged to
accept the agreement voluntarily.

Grandfathering only waives the acceptance requirement. The
:ref:`code_of_conduct` and the :ref:`ai_tool_policy` continue to apply to
everyone, including grandfathered committers.

Contributors who become committers after adoption must accept the agreement as
part of becoming a committer. All other contributors, including occasional and
first-time contributors, must accept the agreement before they can create a
pull request.

Pull requests that are open at the time of adoption may be merged after the
author accepts the agreement. Maintainers may close such pull requests after
reasonable notice if the author does not accept.

The agreement does not change the project license, the existing copyright
policy, or the rights of downstream users.

Security considerations
-----------------------

Granting write access to a repository is a significant trust decision. The
following safeguards should be in place before the agreement is enforced:

- protect the default branch and release branches, and require reviews before
  merging;
- restrict force pushes, branch deletion, and tag creation;
- use CODEOWNERS or equivalent review requirements for sensitive areas;
- grant only the write role, not maintain or admin, for the purpose of
  creating pull requests;
- review team membership periodically and remove inactive members;
- keep an audit record of team membership changes;
- monitor for suspicious activity and handle security reports through the
  project's private security channels.

Administrators should confirm during implementation that the
collaborator-only setting blocks pull requests from forks, and that automated
accounts continue to work as expected.

Alternatives considered
-----------------------

Status quo with moderation
    Keep the current process and rely on maintainers to close low-quality
    contributions. This requires little administration but does not scale and
    does not create an onboarding point.

Adopt the GDAL contribution policy
    A previous attempt to adopt the GDAL policy did not gain traction. Some of
    its ideas, such as CI hardening, remain complementary.

Developer Certificate of Origin (DCO)
    Requiring a ``Signed-off-by`` trailer on every commit provides a
    per-commit attestation and a durable record. It is well understood and
    widely used. This RFC does not require a DCO, but it could be added later
    if the one-time acceptance proves insufficient.

CLA assistant or similar bot
    An automated service can collect signatures, check them on every pull
    request, and prompt contributors to re-accept when the agreement changes.
    This is more robust than manual team management, but it adds a third-party
    dependency and administrative overhead. It could be considered in a
    follow-up.

CI gating
    The approach proposed for PDAL, where a maintainer applies a label to run
    the full CI suite, reduces CI cost. It does not address identity,
    accountability, or community building, so it is complementary rather than
    an alternative.

Restrict pull requests to collaborators
    The chosen approach. It uses a native GitHub feature, creates a clear
    barrier, and provides a simple administrative model. Its main costs are
    that it requires write access and manual administration.

Interaction limits
    GitHub's temporary interaction limits can restrict activity from new
    accounts. They are time-limited and are not a durable contribution policy.

Risks and mitigations
---------------------

Deterring legitimate new contributors
    Provide a clear "how to become a contributor" page, a welcoming response
    to introductory messages, and a documented response time. Review the
    effect after six months.

Administrative bottleneck
    Assign the PSC Chair as primary administrator and a named backup. Document
    the process so that it does not depend on one person.

Privacy and equity
    Make affiliation optional, collect only necessary information, and note
    that the introductory message is public and archived. The PSC may revisit
    the public-list requirement if it proves to be a barrier.

Security of broad write access
    Apply the safeguards in `Security considerations`_, and review access
    periodically.

False sense of legal safety
    Obtain legal review, keep the acceptance record, and consider a DCO or CLA
    bot as a follow-up.

Circumvention through multiple accounts
    No process can prevent this entirely. Monitor for abuse and apply the code
    of conduct and violation-handling process.

Mailing-list moderation
    Introductory messages may be delayed by list moderation. Administrators
    should monitor the queue and follow up with the contributor if a message
    does not appear.

Perceived hostility to AI users
    State explicitly that AI tools are permitted, keep the tone welcoming, and
    allow assistive tools such as translation and copy-editing.

Documentation and communication plan
------------------------------------

When the RFC is adopted, the agreement text should live in one canonical
location, for example a section of :file:`CONTRIBUTING.md` or a dedicated
:file:`.github/CONTRIBUTOR_AGREEMENT.md`. Other documents should link to it
rather than duplicate it. The following should be updated:

- :file:`CONTRIBUTING.md`
- :file:`docs/source/community/contributing.rst`
- :file:`docs/source/community/ai_tool_policy.rst`
- :file:`README.md`
- the pull request and issue templates in :file:`.github/`
- a new :file:`AGENTS.md`

The adoption should be announced on the PROJ mailing list and in the
repositories. The pull request and issue templates should link to the
agreement and explain how to become a signatory. A short "how to become a
contributor" section should describe the flow: read the agreement, send the
introductory message, wait to be added to the team, and then open a pull
request.

Evaluation and review
---------------------

The PSC should review the agreement six months after adoption. The review
should consider:

- the volume and quality of pull requests;
- the time to first review;
- the number of new signatories and the retention of new contributors;
- maintainer workload and reviewer fatigue;
- complaints and violation reports;
- CI usage.

If the agreement is not meeting its goals, or if it is deterring legitimate
contributors, the PSC should revise or roll it back. Material changes to the
agreement require PSC approval and may require signatories to re-accept it.

Open questions
--------------

- Legal review of the licensing wording by OSGeo legal counsel.
- Whether to add a DCO sign-off or a CLA bot in a follow-up.
- Whether to coordinate the approach with GDAL and other OSGeo projects.
- The precise handling of automated accounts and service accounts.
- Whether the public introductory-message requirement should be revisited if
  it proves to be a barrier.

Related issues and PRs
----------------------

- :ref:`ai_tool_policy`
- `GDAL committer guidelines <https://trac.osgeo.org/gdal/wiki/rfc3_commiters>`__
- `PDAL pull request #1 <https://github.com/hobu/PDAL/pull/1>`__: proposed CI
  hardening with a ``ci:full`` label.
- `Cartopy contribution guidelines <https://github.com/SciTools/cartopy/blob/main/.github/CONTRIBUTING.md>`__:
  an example of a contributor agreement.
- `Rust-style contribution clause <https://github.com/busstoptaktik/geodesy#contribution>`__:
  an example of the licensing wording used in the Rust community.
- `0rwx, a simple model of AI usage <https://0rwx.com/>`__: a model for
  describing how AI tools are used.
- The "Current PRs" PSC email thread, November 2026.

Voting history
--------------

To be recorded after the PSC vote.

.. below is an allow-list for spelling checker.

.. spelling::

    0rwx
    AGENTS
    CLA
    CODEOWNERS
    Cartopy
    CI
    DCO
    GDAL
    GitHub
    LLM
    LLMs
    OSGeo
    PDAL
    PSC
    Rust
    assistive
    collaborator-only
    committers
    dependabot
    extractive
    grandfathered
    maintainers
    mitigations
    non-collaborators
    non-extractive
    onboarding
    re-accept
    signatories
    username
