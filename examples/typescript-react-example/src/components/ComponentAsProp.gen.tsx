/* TypeScript file generated by genType. */

// tslint:disable-next-line:no-var-requires
const ComponentAsPropBS = require('./ComponentAsProp.bs');

// tslint:disable-next-line:no-var-requires
const Curry = require('bs-platform/lib/es6/curry.js');

// tslint:disable-next-line:no-var-requires
const ReasonReact = require('reason-react/src/ReasonReact.js');

import {reactElement as ReasonReact_reactElement} from '../../src/shims/ReactShim.shim';

// tslint:disable-next-line:interface-over-type-literal
export type Props = {
  readonly title: ReasonReact_reactElement; 
  readonly description: ReasonReact_reactElement; 
  readonly button?: ReasonReact_reactElement; 
  readonly children?: unknown
};

export const ComponentAsProp: React.ComponentClass<Props> = ReasonReact.wrapReasonForJs(
  ComponentAsPropBS.component,
  (function _(jsProps: Props) {
     return Curry._4(ComponentAsPropBS.make, jsProps.title, jsProps.description, jsProps.button, jsProps.children);
  }));

export default ComponentAsProp;
